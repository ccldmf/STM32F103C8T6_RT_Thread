/**
  ******************************************************************************
  * @file    Modules/GUI/GUI.c
  * @author  CC
  * @version V1.0.0
  * @date    07-25-2020
  * @brief   This file provider the feature of GUI module.
  *
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"
#include "GUI.h"

#include "delay.h"
#include "font.h"
#include "systemColor.h"

#ifdef USING_GUI

/**
  * @brief  Draw circle
  * @param  aX: Position x
  * @param  aY: Position y
  * @param  aRadius: Circle radius
  * @param  aColor: Cicle Color
  * @retval None
  */
void Gui_Circle( uint16_t aX , uint16_t aY , uint16_t aRadius , uint16_t aColor )
{
    unsigned short  a,b;
    int c;
    a = 0;
    b = aRadius;
    c = 3 - 2 * aRadius;
    while( a < b )
    {
        Lcd_DrawPoint( aX + a , aY + b , aColor );     //        7
        Lcd_DrawPoint( aX - a , aY + b , aColor );     //        6
        Lcd_DrawPoint( aX + a , aY - b , aColor );     //        2
        Lcd_DrawPoint( aX - a , aY - b , aColor );     //        3
        Lcd_DrawPoint( aX + b , aY + a , aColor );     //        8
        Lcd_DrawPoint( aX - b , aY + a , aColor );     //        5
        Lcd_DrawPoint( aX + b , aY - a , aColor );     //        1
        Lcd_DrawPoint( aX - b , aY - a , aColor );     //        4

        if( c < 0 ) 
		{
			c = c + 4 * a + 6;
        }
        else
        {
            c = c + 4 * ( a - b ) + 10;
            b -= 1;
        }
		a += 1;
    }
    if( a == b )
    {
        Lcd_DrawPoint( aX + a , aY + b , aColor );
        Lcd_DrawPoint( aX + a , aY + b , aColor );
        Lcd_DrawPoint( aX + a , aY - b , aColor );
        Lcd_DrawPoint( aX - a , aY - b , aColor );
        Lcd_DrawPoint( aX + b , aY + a , aColor );
        Lcd_DrawPoint( aX - b , aY + a , aColor );
        Lcd_DrawPoint( aX + b , aY - a , aColor );
        Lcd_DrawPoint( aX - b , aY - a , aColor );
    }
}

/**
  * @brief  Draw line
  * @param  aStartX: Start x
  * @param  aStartY: Start y
  * @param  aEndX: End x
  * @param  aEndY: End y
  * @param  aColor: Cicle Color
  * @retval None
  */
void Gui_DrawLine( uint16_t aStartX , uint16_t aStartY , uint16_t aEndX , uint16_t aEndY , uint16_t aColor )
{
	int dx,             // difference in x's
	dy,             	// difference in y's
	dx2,            	// dx,dy * 2
	dy2,
	x_inc,          	// amount in pixel space to move during drawing
	y_inc,          	// amount in pixel space to move during drawing
	error,          	// the discriminant i.e. error i.e. decision variable
	index;          	// used for looping


	dx = aEndX - aStartX;
	dy = aEndY - aStartY;

	if( dx >= 0 )
	{
		x_inc = 1;
	}
	else
	{
		x_inc = -1;
		dx    = -dx;
	}

	if( dy >= 0 )
	{
		y_inc = 1;
	}
	else
	{
		y_inc = -1;
		dy    = -dy;
	}

	dx2 = dx << 1;
	dy2 = dy << 1;

	if( dx > dy )
	{
		// initialize error term
		error = dy2 - dx;

		// draw the line
		for( index = 0 ; index <= dx ; index++ )
		{
			Lcd_DrawPoint( aStartX , aStartY , aColor );

			if( error >= 0 ) 
			{
				error -= dx2;

				// move to next line
				aStartY += y_inc;
			} // end if error overflowed

			// adjust the error term
			error += dy2;

			// move to the next pixel
			aStartX += x_inc;
		} 
	} 
	else
	{
		// initialize error term
		error = dx2 - dy;

		// draw the line
		for( index = 0 ; index <= dy ; index++ )
		{
			// set the pixel
			Lcd_DrawPoint( aStartX , aStartY , aColor );

			if( error >= 0 )
			{
				error -= dy2;

				// move to next line
				aStartX += x_inc;
			} // end if error overflowed

			// adjust the error term
			error += dx2;

			// move to the next pixel
			aStartY += y_inc;
		} 
	} 
}

/**
  * @brief  Draw down button
  * @param  aStartX: Start x
  * @param  aStartY: Start y
  * @param  aEndX: End x
  * @param  aEndY: End y
  * @retval None
  */
void GUI_DrawButtonDown( uint16_t aStartX , uint16_t aStartY , uint16_t aEndX , uint16_t aEndY )
{
	Gui_DrawLine( aStartX ,  aStartY , aEndX , aStartY , GRAY2 );  				//H
	Gui_DrawLine( aStartX + 1 , aStartY + 1 , aEndX , aStartY + 1 , GRAY1 );  	//H
	Gui_DrawLine( aStartX ,  aStartY , aStartX , aEndY , GRAY2 );  				//V
	Gui_DrawLine( aStartX + 1, aStartY + 1 , aStartX + 1 , aEndY , GRAY1 );  	//V
	Gui_DrawLine( aStartX ,  aEndY , aEndX , aEndY , WHITE );  					//H
	Gui_DrawLine( aStartX ,  aStartY , aEndX , aEndY , WHITE );  				//V
}

/**
  * @brief  Draw up button
  * @param  aStartX: Start x
  * @param  aStartY: Start y
  * @param  aEndX: End x
  * @param  aEndY: End y
  * @retval None
  */
void GUI_DrawButtonUp( uint16_t aStartX , uint16_t aStartY , uint16_t aEndX , uint16_t aEndY )
{
	Gui_DrawLine( aStartX , aStartY , aEndX , aStartY , WHITE ); 			//H
	Gui_DrawLine( aStartX , aStartY , aStartX , aEndY , WHITE ); 			//V

	Gui_DrawLine( aStartX + 1 , aEndY - 1 , aEndX , aEndY - 1 , GRAY1 );  	//H
	Gui_DrawLine( aStartX ,  aEndY , aEndX , aEndY , GRAY2 );  				//H
	Gui_DrawLine( aEndX -1 , aStartY + 1 , aEndX - 1 , aEndY , GRAY1 );  	//V
    Gui_DrawLine( aEndX , aStartY , aEndX , aEndY , GRAY2 ); 				//V
}

/**
  * @brief  Draw font
  * @param  aX: x position
  * @param  aY: y position
  * @param  aFontColor: font color
  * @param  aBackgroundColor: background color
  * @param	aString: string
  * @retval None
  */
void Gui_DrawFont_GBK16( uint16_t aX , uint16_t aY , uint16_t aFontColor , uint16_t aBackgroundColor , uint8_t *aString )
{
	unsigned char i,j;
	unsigned short k,x0;
	x0 = aX;

	while( *aString )
	{
		if( ( *aString ) < 128 )
		{
			k = *aString;
			if( k == 13 )
			{
				aX = x0;
				aY += 16;
			}
			else
			{
				if( k > 32 ) 
				{
					k-=32; 
				}
				else
				{
					k = 0;
				}

				for( i = 0 ; i < 16 ; i++ )
				{
					for( j = 0 ; j < 8 ; j++ )
					{
						if( asc16[ k * 16 + i ] & ( 0x80 >> j ) )	
						{
							Lcd_DrawPoint( aX + j , aY + i , aFontColor );
						}
						else
						{
							if( aFontColor != aBackgroundColor ) 
							{
								Lcd_DrawPoint( aX + j , aY + i , aBackgroundColor );
							}
						}
					}
				}
				aX += 8;
			}
			aString++;
		}
		else
		{
			for( k = 0 ; k < hz16_num ; k++ )
			{
				if( ( hz16[ k ].Index[ 0 ] == *( aString ) ) && ( hz16[ k ].Index[ 1 ] == *( aString + 1 ) ) )
				{
					for( i = 0 ; i < 16 ; i++ )
					{
						for( j = 0 ; j < 8 ; j++ )
						{
							if( hz16[ k ].Msk[ i * 2 ] & ( 0x80 >> j ) )	
							{
								Lcd_DrawPoint( aX + j , aY + i , aFontColor );
							}
							else 
							{
								if( aFontColor != aBackgroundColor ) 
									Lcd_DrawPoint( aX + j , aY + i , aBackgroundColor );
							}
						}
						for( j = 0 ; j < 8 ; j++ )
						{
							if( hz16[ k ].Msk[ i * 2 + 1 ] & ( 0x80 >> j ) )	
							{
								Lcd_DrawPoint( aX + j + 8 , aY + i , aFontColor );
							}
							else
							{
								if( aFontColor != aBackgroundColor ) 
								{
									Lcd_DrawPoint( aX + j + 8 , aY + i , aBackgroundColor );
								}
							}
						}
					}
				}
			}
			aString += 2;
			aX += 16;
		}
	}
}
/**
  * @brief  Draw number
  * @param  aX: Position x
  * @param  aY: Position y
  * @param  aNumColor: number color
  * @param  aBackgrounColor: background color
  * @param  aNum: number
  * @retval None
  */
void GUI_DrawNum( uint16_t aX , uint16_t aY , uint16_t aNumColor , uint16_t aBackgrounColor , uint16_t aNum ) 
{
	unsigned char i,j,k,c;

    for( i = 0 ; i < 32 ; i++ )
	{
		for( j = 0 ; j < 4 ; j++ )
		{
			c = *( sz32 + aNum * 32 * 4 + i * 4 + j );
			for( k = 0 ; k < 8 ; k++ )
			{

		    	if( c & ( 0x80 >> k ) )	
				{
					Lcd_DrawPoint( aX + j * 8 + k , aY + i , aNumColor );
	    		}
				else 
				{
					if( aNumColor != aBackgrounColor ) 
					{
						Lcd_DrawPoint( aX + j * 8 + k , aY + i , aBackgrounColor );
					}
				}
			}
		}
	}
}

/**
  * @brief  Draw number
  * @param  aImageWidth: image width
  * @param  aImageHigh: image high
  * @param  aImage: image data
  * @retval None
  */
void GUI_DrawImage( uint16_t aImageWidth , uint16_t aImageHigh , const unsigned char *aImage )
{
	int i;
	unsigned char picH,picL;
	Lcd_SetColor( WHITE );

	Lcd_SetRegion( 2 , 0 , aImageWidth - 1 , aImageHigh - 1 );
	for( i= 0 ; i < aImageWidth * aImageHigh ; i++ )
	{
		picL = *( aImage + i * 2 );
		picH = *( aImage + i * 2 + 1 );
		LCD_DrawAWord( picH << 8 | picL );
	}

}

#endif /* USING_GUI */

