#define ENABLE_GRAPHICS
#ifdef ENABLE_GRAPHICS

#ifndef STDIO_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#endif

#define ENABLE_GRAPHICS
#define defer(value) do { result = (value); goto defer; } while (0)
#define BKG_COLOR 0xFF202020
#define G_SWAP_INT(a, b) do { int t = (int) (a); (a) = (int) (b); (b) = t; } while (0)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

inline void g_draw_pixel(u32 *pixels, u32 width, u32 height, u32 y, u32 x, u32 color);
void g_draw_line(u32 *pixels, u32 width, u32 height, int x0, int y0, int x1, int y1, u32 color);
void g_draw_triangle(u32 *pixels, u32 width, u32 height, int x0, int y0, int x1, int y1, int x2, int y2, u32 color);
void g_fill(u32 *pixels, u32 width, u32 height, u32 color);
void g_fill_rect(u32 *pixels, u32 width, u32 height, int x, int y, u32 w, u32 h, u32 color);
void g_fill_triangle(u32 *pixels, u32 width, u32 height, int x0, int y0, int x1, int y1, int x2, int y2, u32 color);
int g_save_to_ppm(u32 *pixels, u32 width, u32 height, char *filepath);

void g_draw_triangle(u32 *pixels, u32 width, u32 height, int x0, int y0, int x1, int y1, int x2, int y2, u32 color)
{
	g_fill(pixels, width, height, BKG_COLOR);
	g_draw_line(pixels, width, height, x0, y0, x1, y1, color);
	g_draw_line(pixels, width, height, x0, y0, x2, y2, color);
	g_draw_line(pixels, width, height, x1, y1, x2, y2, color);
}

void g_sort_triangle_by_y(int *x0, int *y0, int *x1, int *y1, int *x2, int *y2)
{
	if (*y0 > *y1)
	{
		G_SWAP_INT(*y0, *y1);
		G_SWAP_INT(*x0, *x1);
	}
	if (*y1 > *y2)
	{
		G_SWAP_INT(*y1, *y2);
		G_SWAP_INT(*x1, *x2);
	}
	if (*y0 > *y1)
	{
		G_SWAP_INT(*y0, *y1);
		G_SWAP_INT(*x0, *x1);
	}
}

void g_fill_triangle(u32 *pixels, u32 width, u32 height, int x0, int y0, int x1, int y1, int x2, int y2, u32 color)
{

	g_sort_triangle_by_y(&x0, &y0, &x1, &y1, &x2, &y2);
	int dx12 = abs(x1 - x0),
		dy12 = abs(y1 - y0),
		dx13 = abs(x2 - x0),
		dy13 = abs(y2 - y0),
		sx1 = x0 < x1 ? 1 : -1,
		sx2 = x0 < x2 ? 1 : -1,
		sy1 = y0 < y1 ? 1 : -1,
		sy2 = y0 < y2 ? 1 : -1,
		err12 = dx12 - dy12,	
        err13 = dx13 - dy13,
        x12 = x0, y12 = y0,
	    x13 = x0, y13 = y0;
	while (y12 != y1) 
	{
		int e12 = err12 * 2;
		if (e12 > -dy12)
		{
			err12 -= dy12;
			x12 += sx1;
		}
		if (e12 < dx12)
		{
			err12 += dx12;
			y12 += sy1;
			if (y12 == y13)
			{
				for (int i = x13; i < x12; i++)
					g_draw_pixel(pixels, width, height,(u32) i, (u32) y12, color);
			}
		}
		int e13 = err13 * 2;
		if (e13 > -dy13)
		{
			err13 -= dy13;
			x13 += sx2;
		}
		if (e13 < dx13)
		{
			err13 += dx13;
			y13 += sy2;
		}
	}
//	float	xinc12 = (float) dx12 / (float) s12,	
//			yinc12 = (float) dy12 / (float) s12,
//			xinc13 = (float) dx13 / (float) s13,	
//			yinc13 = (float) dy13 / (float) s13,
//			x12 = (float) x0, y12 = y0,
//			x13 = (float) x0, y13 = y0;
//
//		
//		
//		
//		
	//for (int i = 0; i <= s12; ++i)
	//{
	//	if (x12 < x13)
	//	{
	//		for (int j = x12; j < x13; j++)
	//			pixels[(i + (int)y0) * width + j] = color;
	//	}
	//	else if (x12 > x13)
	//	{
	//		for (int j = x13; j < x12; j++)
	//			pixels[(i + (int)y0) * width + j] = color;
	//	}
	//	g_draw_pixel(pixels, width, height, (u32) x13, (u32) y13, color);
	//	x12 += xinc12;
	//	y12 += yinc12;
	//	x13 += xinc13;
	//	y13 += yinc13;
	//}
	g_draw_line(pixels, width, height, x0, y0, x2, y2, color);
	g_draw_line(pixels, width, height, x1, y1, x2, y2, color);
}

int g_save_to_ppm(u32 *pixels, u32 width, u32 height, char *filepath)
{
	int result = 0;
	FILE *fp = fopen(filepath, "wb");

	fprintf(fp, "P6\n# %s\n%u %u\n255\n", filepath, width, height);
	if(ferror(fp)) defer(errno);

	for (u32 i = 0; i < width * height; ++i)
	{
		u32 pixel = pixels[i];
		u8 bytes[3] = {
			(pixel>>(8*0))&0xFF,
			(pixel>>(8*1))&0xFF,
			(pixel>>(8*2))&0xFF,
		};
		fwrite(bytes, sizeof(bytes), 1, fp);
		if(ferror(fp)) defer(errno);
	}

defer:
	if (fp) fclose(fp);
	return (result);
}

void g_fill(u32 *pixels, u32 width, u32 height, u32 color)
{
	for (u32 i = 0; i < width * height; ++i)
		pixels[i] = color;
}

void g_fill_rect(u32 *pixels, u32 width, u32 height,
				 int x, int y, u32 w, u32 h,
				 u32 color)
{
	for (u32 dy = 0; dy < h; ++dy)
	{
		int cy = y + (int) dy;
		if (cy >= 0 && cy < (int) height)
			for (u32 dx = 0; dx < w; ++dx)
			{
				int cx = x + (int) dx;
				if (cx >= 0 && cx < (int) width)
					pixels[cy * width + cx] = color;
			}
	}
}

//void g_draw_line(u32 *pixels, u32 width, u32 height,
//					 int x0, int y0, int x1, int y1,
//					 u32 color)
//{
//	int dx = x1 - x0,
//		dy = y1 - y0,
//		s = abs(dx) < abs(dy) ? abs(dy) : abs(dx);
//	float	incx = (float) dx / (float) s,
//			incy = (float) dy / (float) s,
//			x = (float) x0, y = (float) y0;
//	for (int i = 0; i <= s; ++i)
//	{
//		g_draw_pixel(pixels, width, height, (u32) x, (u32) y, color);
//		y += incy;
//		x += incx;
//	}
//}

void g_draw_line(u32 *pixels, u32 width, u32 height,
					 int x0, int y0, int x1, int y1,
					 u32 color)
{
	int dx = abs(x1 - x0),
		dy = abs(y1 - y0),
		sx = x0 < x1 ? 1 : -1,
		sy = y0 < y1 ? 1 : -1,
		err = dx - dy;
	while (x0 != x1 || y0 != y1)
	{
		int e2 = err * 2;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
		g_draw_pixel(pixels, width, height,(u32) x0, (u32) y0, color);
	}
}

void g_draw_pixel(u32 *pixels, u32 width, u32 height, u32 x, u32 y, u32 color)
{
	if (y > 0 && y < height)
		if(x > 0 && x < width)
			pixels[y * width + x] = color;
}

#endif
