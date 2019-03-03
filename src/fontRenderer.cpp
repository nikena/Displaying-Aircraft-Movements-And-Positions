#include "fontRenderer.hpp"
#include "windowUtils.hpp"

int FontRenderer::getKerningAmount(int firstChar, int secondChar)
{
	std::map<int,std::map<int,int> >::iterator it = (kerningMap.find(firstChar));
	if(it!=kerningMap.end())
	{
		std::map<int,int> secMap = it->second;
		std::map<int,int>::iterator it2 = secMap.find(secondChar);
		if(it2!=secMap.end())
		{
			const int amount = it2->second;
			return amount;
		}
		else return 0;
	}
	return 0;
};
void FontRenderer::drawText(std::string& text,float scale, float x, float y)
{
	const float strx=x;
	const float stry=y - base*scale/fontSpriteSizeY;
	
	int i=0;
	float cursorX=0;
	for(i=0;i<text.length();i++)
	{
		CharGlyph letter= charGlyphMap[text[i]];
		float cx=strx+((cursorX)+letter.xoffset/fontSpriteSizeX)*scale;
		
		float cy=stry+((base-letter.yoffset)/fontSpriteSizeY)*scale;
		
		cursorX+=letter.xadvance/fontSpriteSizeX;
		if(i>0)//Moves it for kerning
		{
			float k = scale*getKerningAmount(text[i-1],text[i])/fontSpriteSizeX;
			cx+=k;
			cursorX+=k;
		}
		float cw=letter.width/fontSpriteSizeX * scale;
		float ch=-letter.height/fontSpriteSizeY * scale;
		
		
		float u=letter.x/fontSpriteSizeX;
		float u2=u+letter.width/fontSpriteSizeX;
		float v=1.0-letter.y/fontSpriteSizeY;
		float v2=(v-letter.height/fontSpriteSizeY);
		
		#define vpb1(a) fontVerticesVec.push_back(a)
		#define vpb5(a,b,c,d,e) vpb1(a);vpb1(b);vpb1(c);vpb1(d);vpb1(e);
		vpb5(cx+cw,cy+ch,0.0f,u2,v2);
		vpb5(cx+cw,cy,0.0f,u2,v);
		vpb5(cx,cy,0.0f,u,v);
		vpb5(cx,cy+ch,0.0f,u,v2);
		#undef vpb5
		#undef vpb1
		
		fontIndicesVec.push_back(indexNum+0);
		fontIndicesVec.push_back(indexNum+1);
		fontIndicesVec.push_back(indexNum+3);
		fontIndicesVec.push_back(indexNum+1);
		fontIndicesVec.push_back(indexNum+2);
		fontIndicesVec.push_back(indexNum+3);
		indexNum+=4;
	}
};
float FontRenderer::getRenderLengthOfText(std::string& text, float scale)
{
	int i=0;
	float cursorX=0;
	for(i=0;i<text.length();i++)
	{
		CharGlyph letter= charGlyphMap[text[i]];
		cursorX+=scale*letter.xadvance/fontSpriteSizeX;
	}
	return cursorX;
};
void FontRenderer::render(float deltaTime)
{
	//Draws the fps on the top right of the screen.
	std::string fps = std::to_string((int)(1/getAverageDeltaTime()));
	const float fpsscale = 0.35f;
	const float fpslen = getRenderLengthOfText(fps,fpsscale);
	drawText(fps,fpsscale, 1.0-fpslen, 1.0);
	flush();
};
void FontRenderer::flush()
{
	fontSprite.bindVAO();
	fontSprite.setVertices(fontVerticesVec.data(),fontVerticesVec.size()*sizeof(float));
	fontSprite.setIndices(fontIndicesVec.data(),fontIndicesVec.size()*sizeof(unsigned int));
	fontSprite.updateVertexAttributes();
	
	indexNum=0;
	fontVerticesVec.clear();
	fontIndicesVec.clear();//Clears to clean text that no longer exists
	
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);//Disables the depth text to draw overlapping characters
	fontSprite.drawSprite();
};
void FontRenderer::initialize()
{
	fontSprite.loadNoInitShape("assets/Fonts/Roboto/roboto-hiero.png",shaderProgramTex);
	std::ifstream robotoFontFile(findFileAbsLocFromRoot("assets/Fonts/Roboto/roboto-hiero.fnt"));
	
	int i=0;
	int charCount=0;
	int kerningCount=0;
	charGlyphMap.clear();
	kerningMap.clear();
	
	//http://www.angelcode.com/products/bmfont/doc/file_format.html
	std::string block1Info;
	std::string block2Common;
	std::string block3Page;
	std::string block4CharCount;
	std::string block4CharCur;
	std::string block5KerningCount;
	std::string block5KerningCur;
	
	std::getline(robotoFontFile, block1Info);
	std::getline(robotoFontFile, block2Common);
	
	sscanf(block2Common.c_str(),"common lineHeight=%d base=%d scaleW=%f scaleH=%f pages=%d packed=%d",
			&lineHeight,&base,&fontSpriteSizeX,&fontSpriteSizeY,&pages,&packed);
	
	std::getline(robotoFontFile, block3Page);
	std::getline(robotoFontFile, block4CharCount);
	
	
	sscanf(block4CharCount.c_str(),"chars count=%d",&charCount);
	for(i=0;i<charCount;i++)
	{
		std::getline(robotoFontFile, block4CharCur);
		
		CharGlyph curChar;
		sscanf(block4CharCur.c_str(),
		"char id=%d       x=%d    y=%d    width=%d    height=%d    xoffset=%d   yoffset=%d   xadvance=%d    page=%d    chnl=%d",
		&(curChar.id),
		&(curChar.x),&(curChar.y),&(curChar.width),&(curChar.height),
		&(curChar.xoffset),&(curChar.yoffset),&(curChar.xadvance),
		&(curChar.page),&(curChar.chnl));
		charGlyphMap[curChar.id]=curChar;
	}
	std::cout<<charCount<<" chars loaded.\n";
	
	std::getline(robotoFontFile, block5KerningCount);
	
	sscanf(block5KerningCount.c_str(),"kernings count=%d",&kerningCount);
	for(i=0;i<kerningCount;i++)
	{
		std::getline(robotoFontFile, block5KerningCur);
		
		int firstChar=0,secondChar=0,amount=0;
		
		sscanf(block5KerningCur.c_str(),
		"kerning first=%d second=%d amount=%d",
		&firstChar,&secondChar,&amount);
		
		kerningMap[firstChar][secondChar]=amount;
	}
	std::cout<<kerningCount<<" kernings loaded.\n";
	robotoFontFile.close();
};
