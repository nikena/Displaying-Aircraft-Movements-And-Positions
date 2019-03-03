#ifndef Font_Renderer_HPP
#define Font_Renderer_HPP
#include <map>
#include "spriteRenderer.hpp"
class CharGlyph
{
	public:
	int id;
	int x,y;
	int width,height;
	int xoffset,yoffset;
	int xadvance;
	int page,chnl;
};
class FontRenderer
{
	public:
	int lineHeight;
	int base;
	float fontSpriteSizeX;
	float fontSpriteSizeY;
	int indexNum=0;//The number of indices.
	
	
	private:
	Sprite fontSprite;
	int pages;
	int packed;
	std::vector<float> fontVerticesVec;
	std::vector<unsigned int> fontIndicesVec;
	
	// int indexNum=0;//The number of indices.

	std::map<int,CharGlyph> charGlyphMap;
	std::map<int,std::map<int,int> > kerningMap;
	
	public:
	
	//Draws a text on the screen.
	//(0,0) is the center of the screen
	//		text - the string to be drawn on to the screen
	//		scale- affects the size of the text on screen
	//		x- screen coordinate, normally between -1.0 and 1.0, left to right
	//		y- screen coordinate, normally between -1.0 and 1.0, down to up
	void drawText(std::string& text,float fontSize, float x, float y);
	//Gets the length of the string as drawn on to the screen.
	//		text- the text to be displayed
	//		scale- affects the size of the text on screen
	float getRenderLengthOfText(std::string& text, float scale);
	//Draws all buffered texts on to the screen. Should only be called once.
	//		deltaTime- the frame time, used to show fps
	void render(float deltaTime);
	
	//Initializes the fontRenderer to load in the font texture and values
	void initialize();
	
	//Flushes text vertices to GPU to be drawn.
	//Clears out old text drawn.
	void flush();

	private:
	//Gets the kerning between two characters
	int getKerningAmount(int firstChar, int secondChar);
};

#endif

