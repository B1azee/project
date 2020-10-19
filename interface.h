#include "TxLib.h"

struct Area
{
    RECT button;
    const char* text = " ";
    bool click = false;
};
COLORREF changeColor(COLORREF color);
/**
 \brief List
*/
struct List
{
    Area items[30];

    const int maxi = 30;
    const int sleep = 80;
    int quantity;
    int x1;
    int y1;
    int x2;
    int y2;
    COLORREF color ;
    COLORREF colorClick ;
    COLORREF colorV ;
    COLORREF colorClickV ;
    /**
     \param[in] quantity number of lines
     \param[in] x1 top x coordinate
     \param[in] y1 left y coordinate
     \param[in] x2 lower x coordinate
     \param[in] y2 right y coordinate
     \param[in] color color of items
     \param[in] colorClick color of the button pressed
    */
    List(int quantity_,int x1_,int y1_,int x2_,int y2_,COLORREF color_,COLORREF colorClick_)
    {
        quantity = quantity_;
        x1 = x1_;
        y1 = y1_;
        x2 = x2_;
        y2 = y2_;
        color = color_;
        colorClick = colorClick_;

        colorV = changeColor(color);
        colorClickV = changeColor(colorClick);
    }
    /**
     \brief paint List
    */
    void paintItems()
    {

        txSetFillColor(color);
        txRectangle(x1,y1,x2,y2);
        int raz = y2 - y1;
        int rast = raz / quantity;
        txSelectFont("Arial",20)	;
        for(int i = 0; i < quantity; i++)
        {
            items[i].button = {0,0,0,0};
            txLine(x1,y1 + rast * i,x2,y1 + rast * i);
            items[i].button = {x1,y1 + rast * i,x2,y1 + rast * i + rast};
            if(items[i].click == true)
            {
                txSetFillColor(colorClick);
                txRectangle(x1,y1 + rast * i,x2,y1 + rast * i + rast);
            }
            txDrawText(x1,y1 + rast * i,x2,y1 + rast * i + rast,items[i].text);
        }
    }
    /**
     \brief enter line text
    */
    void textItems(const char* text1 = " ",const char* text2 = " ",
                   const char* text3 = " ",const char* text4 = " ",
                   const char* text5 = " ",const char* text6 = " ",
                   const char* text7 = " ",const char* text8 = " ",
                   const char* text9 = " ",const char* text10 = " ")
    {

        items[0].text = text1;
        items[1].text = text2;
        items[2].text = text3;
        items[3].text = text4;
        items[4].text = text5;
        items[5].text = text6;
        items[6].text = text7;
        items[7].text = text8;
        items[8].text = text9;
        items[9].text = text10;
    }
    /**
     \brief checks which line is clicked on
    */

    void check()
    {
        for(int i = 0; i < quantity; i++)
        {
            if(In (txMousePos(), items[i].button))
            {
                if(!items[i].click)
                {

                    txSetFillColour(colorV);
                    txRectangle(items[i].button.left,items[i].button.top,items[i].button.right,items[i].button.bottom);
                    txDrawText(items[i].button.left,items[i].button.top,items[i].button.right,items[i].button.bottom,items[i].text);
                }
                else
                {
                    txSetFillColour(colorClickV);
                    txRectangle(items[i].button.left,items[i].button.top,items[i].button.right,items[i].button.bottom);
                    txDrawText(items[i].button.left,items[i].button.top,items[i].button.right,items[i].button.bottom,items[i].text);
                }


                if(txMouseButtons() & 1 && In (txMousePos(), items[i].button))
                {
                    items[i].click = !items[i].click;
                    for(int n = 0; n < quantity; n++)
                        if(!(n == i))
                        {
                            items[n].click = false;
                        }
                    txSleep(sleep);
                }
            }
        }
    }

    /**
     \brief returns the number of the pressed line or 0 when nothing is pressed
     \return line number; 0 when nothing is pressed
    */
    int returnItems()
    {
        int ret = 0;
        for(int i = 0; i < quantity; i++)
        {
            if  (items[i].click == true)
            {
                ret = i + 1;
            }

        }
        return ret;
    }
};

/**
 \brief Button
*/
struct Button
{
    RECT area;
    const int sleep = 80;
    int x1;
    int y1;
    int x2;
    int y2;
    const char* text;
    COLORREF color ;
    COLORREF colorV ;
    bool type;
    /**
     \param[in] x1 top x coordinate
     \param[in] y1 left y coordinate
     \param[in] x2 lower x coordinate
     \param[in] y2 right y coordinate
     \param[in] color color of button
     \param[in] text text in button
    */
    Button(int x1_,int y1_,int x2_,int y2_,COLORREF color_,const char* text_ = " ")
    {
        x1 = x1_;
        y1 = y1_;
        x2 = x2_;
        y2 = y2_;
        text = text_;
        color = color_;
        colorV = changeColor(color);
        area = {x1,y1,x2,y2};
    }
    /**
     \brief paint button
    */
    void paint()
    {
        txSetFillColor(color);
        txRectangle(x1,y1,x2,y2);
        txSelectFont("Arial",20);
        txDrawText(x1,y1,x2,y2,text);
    }
    /**
     \brief checks when button is clicked on
    */
    bool check()
    {
        bool ret = false;
        if(In (txMousePos(), area))
        {
            txSetFillColour(colorV);
            txRectangle(x1,y1,x2,y2);
            txDrawText(x1,y1,x2,y2,text);

            if(txMouseButtons() & 1)
            {
                ret = true;
                txSleep(sleep);
            }

        }
        return ret;
    }
};

COLORREF changeColor(COLORREF color)
{
    int r,g,b;
    const int colorDelta = 10;
    if(GetRValue(color) > 240)
    {
        r = GetRValue(color) - 4*colorDelta;
    }
    else
    {
        r = GetRValue(color) + colorDelta;
    }
    if(GetRValue(color) == 0)
    {
        r = 0;
    }

    if(GetGValue(color) > 240)
    {
        g = GetGValue(color) - colorDelta;
    }
    else
    {
        g = GetGValue(color) + 4*colorDelta;
    }
    if(GetGValue(color) == 0)
    {
        g = 0;
    }

    if(GetBValue(color) > 240)
    {
        b = GetBValue(color) - 4*colorDelta;
    }
    else
    {
        b = GetBValue(color) + colorDelta;
    }
    if(GetBValue(color) == 0)
    {
        b = 0;
    }
    COLORREF changedColor = RGB(r,g,b);
    return changedColor;
}

