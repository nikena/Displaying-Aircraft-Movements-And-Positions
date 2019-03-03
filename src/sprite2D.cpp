#include <string>
#include "spriteRenderer.hpp"
#include "sprite2D.hpp"
class Sprite2D : public Sprite{
    public:
    float x, y, w, h;
    bool display;
    bool clicked = false;
    std::string name;
    Sprite2D(){
        this->display = false;
	};
    
    // x1 - left bottom x coord
    // y1 - left bottom y coord
    // w1 - width
    // h1 - height
    void setTo2DDimensions(float x1, float y1, float w1, float h1){
        Sprite::setTo2DDimensions(x1, y1, w1, h1);
        x = x1;
        y = y1;
        w = w1;
        h = h1;
    }

    bool contains(float x1, float y1){
    	if(x1 >= x && y1 >= y){
            if(x1 <= x + w && y1 <= y + h){
                return true;
            }
    	}
    	return false;
    }

    void setToDisplay(){
        this->display = true;
    }

    void setToHide(){
        this->display = false;
    }

    void setName(std::string name){
        this->name = name;
    }

    float getX(){
        return this->x;
    }

    float getY(){
        return this->y;
    }

    float getWidth(){
        return this->w;
    }

    float getHeight(){
        return this->h;
    }
 
    bool isDisplay(){
        return this->display;
    }

    bool isClicked(){
        return this->clicked;
    }

    std::string getName(){
        return this->name;
    }
};
