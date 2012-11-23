/*
 * Author: Fuang.Cao
 * Email: cavan.cfa@gmail.com
 * Date: Tue Nov 20 16:09:31 CST 2012
 */

#include <cavan.h>
#include <cavan/display.h>
#include <cavan/calculator.h>
#include <math.h>

int cavan_build_line_equation(int x1, int y1, int x2, int y2, double *a, double *b)
{
	int x_diff;

	// println("x1 = %d, y1 = %d, x2 = %d, y2 = %d", x1, y1, x2, y2);

	x_diff = x2 - x1;
	if (x_diff > -5 && x_diff < 5)
	{
		*a = 0;
		*b = 0;
		return -EINVAL;
	}

	*a = ((double)(y2 - y1)) / x_diff;
	*b = y1 - *a * x1;

	return 0;
}

int cavan_display_draw_line_horizon(struct cavan_display_device *display, int x1, int y1, int x2, int y2)
{
	double a, b;
	cavan_display_color_t color;
	cavan_display_draw_point_handler_t handler;

	handler = display->draw_point;
	color = display->pen_color;

	if (x1 == x2)
	{
		if (y1 < y2)
		{
			while (y1 <= y2)
			{
				handler(display, x1, y1, color);
				y1++;
			}
		}
		else
		{
			while (y1 >= y2)
			{
				handler(display, x1, y1, color);
				y1--;
			}
		}

		return 0;
	}

	cavan_build_line_equation(x1, y1, x2, y2, &a, &b);

	if (x1 < x2)
	{
		while (x1 <= x2)
		{
			handler(display, x1, a * x1 + b, color);
			x1++;
		}
	}
	else
	{
		while (x1 >= x2)
		{
			handler(display, x1, a * x1 + b, color);
			x1--;
		}
	}

	return 0;
}

int cavan_display_draw_line_vertical(struct cavan_display_device *display, int x1, int y1, int x2, int y2)
{
	double a, b;
	cavan_display_color_t color;
	cavan_display_draw_point_handler_t handler;

	handler = display->draw_point;
	color = display->pen_color;

	if (y1 == y2)
	{
		if (x1 < x2)
		{
			while (x1 <= x2)
			{
				handler(display, x1, y1, color);
				x1++;
			}
		}
		else
		{
			while (x1 >= x2)
			{
				handler(display, x1, y1, color);
				x1--;
			}
		}

		return 0;
	}

	cavan_build_line_equation(y1, x1, y2, x2, &a, &b);

	if (y1 < y2)
	{
		while (y1 <= y2)
		{
			handler(display, a * y1 + b, y1, color);
			y1++;
		}
	}
	else
	{
		while (y1 >= y2)
		{
			handler(display, a * y1 + b, y1, color);
			y1--;
		}
	}

	return 0;
}

int cavan_display_draw_line_dummy(struct cavan_display_device *display, int x1, int y1, int x2, int y2)
{
	int ret;

	if (x1 < 0 || x1 >= display->xres || x2 < 0 || x2 >= display->xres)
	{
		return -EINVAL;
	}

	if (y1 < 0 || y1 >= display->yres || y2 < 0 || y2 >= display->yres)
	{
		return -EINVAL;
	}

	ret = cavan_display_draw_line_horizon(display, x1, y1, x2, y2);

	return ret < 0 ? ret : cavan_display_draw_line_vertical(display, x1, y1, x2, y2);
}

int cavan_display_draw_rect_dummy(struct cavan_display_device *display, int left, int top, int width, int height)
{
	int i;
	int right, bottom;
	cavan_display_color_t color;
	cavan_display_draw_point_handler_t handler;

	handler = display->draw_point;
	color = display->pen_color;

	right = left + width - 1;
	if (right >= display->xres)
	{
		right = display->xres - 1;
	}

	if (left < 0)
	{
		left = 0;
	}

	bottom = top + height - 1;
	if (bottom >= display->yres)
	{
		bottom = display->yres - 1;
	}

	if (top < 0)
	{
		top = 0;
	}

	for (i = left; i <= right; i++)
	{
		handler(display, i, top, color);
		handler(display, i, bottom, color);
	}

	for (i = top; i <= bottom; i++)
	{
		handler(display, left, i, color);
		handler(display, right, i, color);
	}

	return 0;
}

int cavan_display_fill_rect_dummy(struct cavan_display_device *display, int left, int top, int width, int height)
{
	int right, bottom;
	int x, y;
	cavan_display_color_t color;
	cavan_display_draw_point_handler_t handler;

	handler = display->draw_point;
	color = display->pen_color;

	right = left + width - 1;
	if (right >= display->xres)
	{
		right = display->xres - 1;
	}

	if (left < 0)
	{
		left = 0;
	}

	bottom = top + height - 1;
	if (bottom >= display->yres)
	{
		bottom = display->yres - 1;
	}

	if (top < 0)
	{
		top = 0;
	}

	for (y = top; y <= bottom; y++)
	{
		for (x = left; x <= right; x++)
		{
			handler(display, x, y, color);
		}
	}

	return 0;
}

int cavan_display_draw_circle_dummy(struct cavan_display_device *display, int x, int y, int r)
{
	int rr;
	int i;
	int tmp;
	cavan_display_color_t color;
	cavan_display_draw_point_handler_t handler;

	if (x - r < 0 || x + r >= display->xres || y - r < 0 || y + r >= display->yres)
	{
		return -EINVAL;
	}

	handler = display->draw_point;
	color = display->pen_color;
	rr = r * r;

	for (i = 0; i < r; i++)
	{
		tmp = sqrt(rr - i * i);

		handler(display, x + i, y + tmp, color);
		handler(display, x + i, y - tmp, color);
		handler(display, x - i, y + tmp, color);
		handler(display, x - i, y - tmp, color);

		handler(display, x + tmp, y + i, color);
		handler(display, x + tmp, y - i, color);
		handler(display, x - tmp, y + i, color);
		handler(display, x - tmp, y - i, color);
	}

	return 0;
}

int cavan_display_fill_circle_dummy(struct cavan_display_device *display, int x, int y, int r)
{
	int rr;
	int i;
	int tmp, left, right, top, bottom;
	cavan_display_color_t color;
	cavan_display_draw_point_handler_t handler;

	if (x - r < 0 || x + r >= display->xres || y - r < 0 || y + r >= display->yres)
	{
		return -EINVAL;
	}

	handler = display->draw_point;
	color = display->pen_color;
	rr = r * r;

	for (i = 0; i < r; i++)
	{
		tmp = sqrt(rr - i * i);

		for (left = x - i, right = x + i, top = y + tmp, bottom = y - tmp; top <= bottom; top++)
		{
			handler(display, left, top, color);
			handler(display, right, top, color);
		}

		for (left = x - tmp, right = x + tmp, top = y - i, bottom = y + i; left <= right; left++)
		{
			handler(display, left, top, color);
			handler(display, left, bottom, color);
		}
	}

	return 0;
}

int cavan_display_draw_ellipse_dummy(struct cavan_display_device *display, int x, int y, int width, int height)
{
	double aa, bb;
	int tmp;
	int i;
	cavan_display_color_t color;
	cavan_display_draw_point_handler_t handler;

	aa = ((double)width) / 2;
	bb = ((double)height) / 2;

	if (x - aa < 0 || x + aa >= display->xres || y - bb < 0 || y + bb >= display->yres)
	{
		return -EINVAL;
	}

	aa *= aa;
	bb *= bb;
	handler = display->draw_point;
	color = display->pen_color;

	for (i = width >> 1; i >= 0; i--)
	{
		tmp = sqrt(bb - (bb * i * i / aa));

		handler(display, x + i, y + tmp, color);
		handler(display, x + i, y - tmp, color);
		handler(display, x - i, y + tmp, color);
		handler(display, x - i, y - tmp, color);
	}

	for (i = height >> 1; i >= 0; i--)
	{
		tmp = sqrt(aa - (aa * i * i / bb));

		handler(display, x + tmp, y + i, color);
		handler(display, x + tmp, y - i, color);
		handler(display, x - tmp, y + i, color);
		handler(display, x - tmp, y - i, color);
	}

	return 0;
}

int cavan_display_fill_ellipse_dummy(struct cavan_display_device *display, int x, int y, int width, int height)
{
	double aa, bb;
	int tmp, left, right, top, bottom;
	int i;
	cavan_display_color_t color;
	cavan_display_draw_point_handler_t handler;

	aa = ((double)width) / 2;
	bb = ((double)height) / 2;

	if (x - aa < 0 || x + aa >= display->xres || y - bb < 0 || y + bb >= display->yres)
	{
		return -EINVAL;
	}

	aa *= aa;
	bb *= bb;
	handler = display->draw_point;
	color = display->pen_color;

	for (i = width >> 1; i >= 0; i--)
	{
		tmp = sqrt(bb - (bb * i * i / aa));

		for (left = x - i, right = x + i, top = y - tmp, bottom = y + tmp; top <= bottom; top++)
		{
			handler(display, left, y + tmp, color);
			handler(display, right, y + tmp, color);
		}
	}

	for (i = height >> 1; i >= 0; i--)
	{
		tmp = sqrt(aa - (aa * i * i / bb));

		for (left = x - tmp, right = x + tmp, top = y - i, bottom = y + i; left <= right; left++)
		{
			handler(display, left, top, color);
			handler(display, left, bottom, color);
		}
	}

	return 0;
}

int cavan_display_draw_polygon_dummy(struct cavan_display_device *display, cavan_display_point_t *points, size_t count)
{
	unsigned int i;
	int ret;

	if (count < 3)
	{
		return -EINVAL;
	}

	for (i = 0, count--; i < count; i++)
	{
		ret = cavan_display_draw_line_dummy(display, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		if (ret < 0)
		{
			return ret;
		}
	}

	return cavan_display_draw_line_dummy(display, points[0].x, points[0].y, points[count].x, points[count].y);
}

int max3i(int a, int b, int c)
{
	if (b > a)
	{
		a = b;
	}

	return c > a ? c : a;
}

int min3i(int a, int b, int c)
{
	if (b < a)
	{
		a = b;
	}

	return c < a ? c : a;
}

void cavan_display_show_points(const cavan_display_point_t *points, size_t size)
{
	const cavan_display_point_t *end;

	for (end = points + size; points < end; points++)
	{
		println("[%d, %d]", points->x, points->y);
	}
}

void cavan_display_point_sort_x(cavan_display_point_t *start, cavan_display_point_t *end)
{
	cavan_display_point_t mid, *start_bak, *end_bak;

	if (start >= end)
	{
		return;
	}

	mid = *start;
	start_bak = start;
	end_bak = end;

	while (1)
	{
		for (; start < end && mid.x <= end->x; end--);
		if (start < end)
		{
			*start++ = *end;
		}
		else
		{
			break;
		}

		for (; start < end && mid.x >= start->x; start++);
		if (start < end)
		{
			*end-- = *start;
		}
		else
		{
			break;
		}
	}

	*start = mid;

	if (start_bak < start)
	{
		cavan_display_point_sort_x(start_bak, start - 1);
	}

	if (end_bak > end)
	{
		cavan_display_point_sort_x(end + 1, end_bak);
	}
}

int cavan_display_fill_triangle_half(struct cavan_display_device *display, cavan_display_point_t *p1, cavan_display_point_t *p2, double a1, double b1, double a2, double b2)
{
	int left, right, top, bottom;
	cavan_display_color_t color;
	cavan_display_draw_point_handler_t handler;

	// println("left = %d, right = %d", left, right);
	// println("a1 = %lf, b1 = %lf, a2 = %lf, b2 = %lf", a1, b1, a2, b2);

	handler = display->draw_point;
	color = display->pen_color;

	left = p1->x;
	right = p2->x;

	if ((a1 == 0 && b1 == 0) || (a2 == 0 && b2 == 0))
	{
		if (p1->y < p2->y)
		{
			top = p1->y;
			bottom = p2->y;
		}
		else
		{
			top = p2->y;
			bottom = p1->y;
		}

		while (left <= right)
		{
			int i;

			for (i = top; i <= bottom; i++)
			{
				handler(display, left, i, color);
			}

			left++;
		}

		return 0;
	}

	while (left <= right)
	{
		top = a1 * left + b1;
		bottom = a2 * left + b2;

		while (top <= bottom)
		{
			handler(display, left, top, color);
			top++;
		}

		left++;
	}

	return 0;
}

int cavan_display_fill_triangle_dummy(struct cavan_display_device *display, cavan_display_point_t *points)
{
	double a[3], b[3];
	cavan_display_point_t *p0, *p1, *p2;

	if (points[0].x < points[1].x)
	{
		p0 = points;
		p1 = points + 1;
	}
	else
	{
		p0 = points + 1;
		p1 = points;
	}

	if (points[2].x < p0->x)
	{
		p2 = p1;
		p1 = p0;
		p0 = points + 2;
	}
	else if (points[2].x < p1->x)
	{
		p2 = p1;
		p1 = points + 2;
	}
	else
	{
		p2 = points + 2;
	}

	cavan_build_line_equation(p0->x, p0->y, p1->x, p1->y, a, b);
	cavan_build_line_equation(p0->x, p0->y, p2->x, p2->y, a + 1, b + 1);
	cavan_build_line_equation(p2->x, p2->y, p1->x, p1->y, a + 2, b + 2);

	if (a[1] == 0 && b[1] == 0)
	{
		return -EINVAL;
	}

	if (p1->y < (p1->x * a[1] + b[1]))
	{
		// pr_bold_pos();
		cavan_display_fill_triangle_half(display, p0, p1, a[0], b[0], a[1], b[1]);
		cavan_display_fill_triangle_half(display, p1, p2, a[2], b[2], a[1], b[1]);
	}
	else
	{
		// pr_bold_pos();
		cavan_display_fill_triangle_half(display, p0, p1, a[1], b[1], a[0], b[0]);
		cavan_display_fill_triangle_half(display, p1, p2, a[1], b[1], a[2], b[2]);
	}

	return 0;
}

int cavan_display_fill_polygon_dummy(struct cavan_display_device *display, cavan_display_point_t *points, size_t count)
{
	int ret;
	cavan_display_point_t *p, *p_end;
	cavan_display_point_t point_buff[3];

	if (count < 3)
	{
		return -EINVAL;
	}

	for (p = points + 1, p_end = p + count - 2; p < p_end; p++)
	{
		point_buff[0] = points[0];
		point_buff[1] = p[0];
		point_buff[2] = p[1];

		ret = cavan_display_fill_triangle_dummy(display, point_buff);
		if (ret < 0)
		{
			return ret;
		}
	}

	return 0;
}

int cavan_build_polygon_points(struct cavan_display_device *display, cavan_display_point_t *points, size_t count, int x, int y, int r, int rotation)
{
	double angle, avg_angle;
	cavan_display_point_t *point_end;

	if (count < 3)
	{
		return -EINVAL;
	}

	avg_angle = PI * 2 / count;

	for (point_end = points + count, angle = (PI * rotation) / 180 ; points < point_end; points++, angle += avg_angle)
	{
		points->x = x + r * cos(angle);
		points->y = y + r * sin(angle);
	}

	return 0;
}

int cavan_display_draw_polygon_standard(struct cavan_display_device *display, size_t count, int x, int y, int r, int rotation)
{
	int ret;
	cavan_display_point_t points[count];

	ret = cavan_build_polygon_points(display, points, count, x, y, r, rotation);

	return ret < 0 ? ret : cavan_display_draw_polygon_dummy(display, points, count);
}

int cavan_display_fill_polygon_standard(struct cavan_display_device *display, size_t count, int x, int y, int r, int rotation)
{
	int ret;
	cavan_display_point_t points[count];

	ret = cavan_build_polygon_points(display, points, count, x, y, r, rotation);

	return ret < 0 ? ret : cavan_display_fill_polygon_dummy(display, points, count);
}

int cavan_display_draw_polygon_standard2(struct cavan_display_device *display, size_t count, int x, int y, int r, int rotation)
{
	int ret;
	cavan_display_point_t points[count];
	cavan_display_point_t *p1, *p2, *end_p;

	ret = cavan_build_polygon_points(display, points, count, x, y, r, rotation);
	if (ret < 0)
	{
		return ret;
	}

	for (p1 = points, end_p = points + count; p1 < end_p; p1++)
	{
		for (p2 = points; p2 < p1; p2++)
		{
			ret = cavan_display_draw_line_dummy(display, p1->x, p1->y, p2->x, p2->y);
			if (ret < 0)
			{
				return ret;
			}
		}

		for (p2 = p1 + 1; p2 < end_p; p2++)
		{
			ret = cavan_display_draw_line_dummy(display, p1->x, p1->y, p2->x, p2->y);
			if (ret < 0)
			{
				return ret;
			}
		}
	}

	return 0;
}

int cavan_calculate_line_cross_point(int x1, int x2, double a1, double b1, double a2, double b2, cavan_display_point_t *point)
{
	if (a1 == a2)
	{
		return -EINVAL;
	}

	if (a1 == 0 && b1 == 0)
	{
		point->x = x1;
		point->y = a2 * x1 + b2;
	}
	else if (a2 == 0 && b2 == 0)
	{
		point->x = x2;
		point->y = a1 * x2 + b1;
	}
	else
	{
		point->x = (b1 - b2) / (a2 - a1);
		point->y = a1 * point->x + b1;
	}

	return 0;
}

int cavan_calculate_polygo_cross_points(cavan_display_point_t *points, cavan_display_point_t *cross_points, size_t count)
{
	size_t i;
	int ret;
	cavan_display_point_t *p0, *p1, *p2, *p3;
	double a1, a2, b1, b2;

	if (count < 5)
	{
		return -EINVAL;
	}

	for (i = 0; i < count; i++)
	{
		p0 = points + i;
		p2 = points + (i + 2) % count;
		cavan_build_line_equation(p0->x, p0->y, p2->x, p2->y, &a1, &b1);

		p1 = points + (i + 1) % count;
		p3 = points + (i + 3) % count;
		cavan_build_line_equation(p1->x, p1->y, p3->x, p3->y, &a2, &b2);

		ret = cavan_calculate_line_cross_point(p0->x, p1->x, a1, b1, a2, b2, cross_points + i);
		if (ret < 0)
		{
			return ret;
		}
	}

	return 0;
}

int cavan_display_fill_polygon_standard2(struct cavan_display_device *display, size_t count, int x, int y, int r, int rotation)
{
	int ret;
	size_t i;
	cavan_display_point_t points[count];
	cavan_display_point_t cross_points[count];
	cavan_display_point_t triangle_points[3];

	if (count < 5)
	{
		return cavan_display_fill_polygon_standard(display, count, x, y, r, rotation);
	}

	ret = cavan_build_polygon_points(display, points, count, x, y, r, rotation);
	if (ret < 0)
	{
		return ret;
	}

	ret = cavan_calculate_polygo_cross_points(points, cross_points, count);
	if (ret < 0)
	{
		return ret;
	}

	for (i = 0; i < count; i++)
	{
		triangle_points[0] = cross_points[i];
		triangle_points[1] = cross_points[(i + 1) % count];
		triangle_points[2] = points[(i + 2) % count];

		cavan_display_fill_triangle_dummy(display, triangle_points);
	}

	return 0;
}

int cavan_display_draw_polygon_standard3(struct cavan_display_device *display, size_t count, int x, int y, int r, int rotation)
{
	int ret;
	cavan_display_point_t points[count];
	size_t i, j;

	ret = cavan_build_polygon_points(display, points, count, x, y, r, rotation);
	if (ret < 0)
	{
		return ret;
	}

	for (i = 0; i < count; i++)
	{
		j = (i + 2) % count;

		ret = cavan_display_draw_line_dummy(display, points[i].x, points[i].y, points[j].x, points[j].y);
		if (ret < 0)
		{
			return ret;
		}
	}

	return 0;
}

int cavan_display_fill_polygon_standard3(struct cavan_display_device *display, size_t count, int x, int y, int r, int rotation)
{
	int ret;
	unsigned int i;
	cavan_display_point_t points[count];
	cavan_display_point_t cross_points[count];

	if (count < 5)
	{
		return cavan_display_fill_polygon_standard(display, count, x, y, r, rotation);
	}

	ret = cavan_build_polygon_points(display, points, count, x, y, r, rotation);
	if (ret < 0)
	{
		return ret;
	}

	ret = cavan_calculate_polygo_cross_points(points, cross_points, count);
	if (ret < 0)
	{
		return ret;
	}

	cavan_display_fill_polygon_dummy(display, cross_points, count);

	for (i = 0; i < count; i++)
	{
		cavan_display_point_t triangle_points[3];

		triangle_points[0] = cross_points[i];
		triangle_points[1] = cross_points[(i + 1) % count];
		triangle_points[2] = points[(i + 2) % count];

		cavan_display_fill_triangle_dummy(display, triangle_points);
	}

	return 0;
}

int cavan_display_draw_polygon_standard4(struct cavan_display_device *display, size_t count, int x, int y, int r, int rotation)
{
	int ret;

	ret = cavan_display_draw_polygon_standard3(display, count, x, y, r, rotation);
	if (ret < 0)
	{
		return ret;
	}

	return cavan_display_draw_circle_dummy(display, x, y, r);
}

int cavan_display_memory_xfer_dummy(struct cavan_display_device *display, struct cavan_display_memory *mem, bool read)
{
	char *data;
	size_t line_size;
	char *p, *p_end;
	int width;
	int right, bottom;

	right = mem->x + mem->width;
	if (right > display->xres)
	{
		right = display->xres;
	}

	if (mem->x < 0)
	{
		mem->x = 0;
	}

	bottom = mem->y + mem->height;
	if (bottom > display->yres)
	{
		bottom = display->yres;
	}

	if (mem->y < 0)
	{
		mem->y = 0;
	}

	if (mem->x >= right || mem->y >= bottom)
	{
		return 0;
	}

	mem->width = right - mem->x;
	mem->height = bottom - mem->y;

	width = mem->width * display->bpp_byte;
	line_size = display->bpp_byte * display->xres;

	p = (char *)display->fb_base + mem->y * line_size + mem->x * display->bpp_byte;
	p_end = p + mem->height * line_size;

	data = mem->data;

	if (read)
	{
		while (p < p_end)
		{
			mem_copy32(data, p, width);

			data += width;
			p += line_size;
		}
	}
	else
	{
		while (p < p_end)
		{
			mem_copy32(p, data, width);

			data += width;
			p += line_size;
		}
	}

	return 0;
}

size_t cavan_display_mesure_text_dummy(struct cavan_display_device *display, const char *text)
{
	return text_len(text);
}

int cavan_display_draw_text_dummy(struct cavan_display_device *display, int x, int y, const char *text)
{
	return 0;
}

void cavan_display_set_color_dummy(struct cavan_display_device *display, cavan_display_color_t color)
{
	display->pen_color = color;
}

void cavan_display_destory_dummy(struct cavan_display_device *display)
{
}

int cavan_display_check(struct cavan_display_device *display)
{
	if (display == NULL)
	{
		pr_red_info("display == NULL");
		return -EINVAL;
	}

	if (display->xres < 1 || display->yres < 1 || display->bpp_byte < 1)
	{
		pr_red_info("display->xres < 1 || display->yres < 1 || display->bpp_byte < 1");
		return -EINVAL;
	}

	if (display->draw_point == NULL || display->refresh == NULL)
	{
		pr_red_info("display->draw_point == NULL || display->refresh == NULL");
		return -EINVAL;
	}

	if (display->build_color == NULL)
	{
		pr_red_info("display->build_color == NULL");
		return -EINVAL;
	}

	if (display->display_memory_xfer == NULL && display->fb_base == NULL)
	{
		pr_red_info("display->display_memory_xfer == NULL && display->fb_base == NULL");
		return -EINVAL;
	}

	if (display->mesure_text == NULL)
	{
		display->mesure_text = cavan_display_mesure_text_dummy;
	}

	if (display->draw_text == NULL)
	{
		display->draw_text = cavan_display_draw_text_dummy;
	}

	if (display->draw_line == NULL)
	{
		display->draw_line = cavan_display_draw_line_dummy;
	}

	if (display->draw_rect == NULL)
	{
		display->draw_rect = cavan_display_draw_rect_dummy;
	}

	if (display->fill_rect == NULL)
	{
		display->fill_rect = cavan_display_fill_rect_dummy;
	}

	if (display->draw_circle == NULL)
	{
		display->draw_circle = cavan_display_draw_circle_dummy;
	}

	if (display->fill_circle == NULL)
	{
		display->fill_circle = cavan_display_fill_circle_dummy;
	}

	if (display->draw_ellipse == NULL)
	{
		display->draw_ellipse = cavan_display_draw_ellipse_dummy;
	}

	if (display->fill_ellipse == NULL)
	{
		display->fill_ellipse = cavan_display_fill_ellipse_dummy;
	}

	if (display->draw_polygon == NULL)
	{
		display->draw_polygon = cavan_display_draw_polygon_dummy;
	}

	if (display->fill_triangle == NULL)
	{
		display->fill_triangle = cavan_display_fill_triangle_dummy;
	}

	if (display->fill_polygon == NULL)
	{
		display->fill_polygon = cavan_display_fill_polygon_dummy;
	}

	if (display->display_memory_xfer == NULL)
	{
		display->display_memory_xfer = cavan_display_memory_xfer_dummy;
	}

	if (display->set_color == NULL)
	{
		display->set_color = cavan_display_set_color_dummy;
	}

	if (display->destory == NULL)
	{
		display->destory = cavan_display_destory_dummy;
	}

	return 0;
}

struct cavan_display_memory *cavan_display_memory_alloc(struct cavan_display_device *display, size_t width, size_t height)
{
	struct cavan_display_memory *mem;
	size_t size;

	size = width * height * display->bpp_byte;
	mem = malloc(sizeof(*mem) + size);
	if (mem == NULL)
	{
		pr_error_info("malloc");
		return NULL;
	}

	mem->width = mem->height = 0;
	mem->width_max = width;
	mem->height_max = height;

	return mem;
}

struct cavan_display_memory_rect *cavan_display_memory_rect_alloc(struct cavan_display_device *display, size_t width, size_t height, int border_width)
{
	struct cavan_display_memory *mem;
	struct cavan_display_memory_rect *mem_rect;
	size_t hsize, vsize;

	hsize = sizeof(struct cavan_display_memory) + width * border_width * display->bpp_byte;
	vsize = sizeof(struct cavan_display_memory) + border_width * (height - border_width * 2) * display->bpp_byte;

	mem_rect = malloc(sizeof(*mem_rect) + (hsize + vsize) * 2);
	if (mem_rect == NULL)
	{
		pr_error_info("malloc");
		return mem_rect;
	}

	mem = (struct cavan_display_memory *)(mem_rect + 1);
	mem->width = mem->height = 0;
	mem->width_max = width;
	mem->height_max = border_width;
	mem_rect->mems[0] = mem;

	mem = (struct cavan_display_memory *)(((byte *)mem) + hsize);
	mem->width = mem->height = 0;
	mem->width_max = width;
	mem->height_max = border_width;
	mem_rect->mems[1] = mem;

	mem = (struct cavan_display_memory *)(((byte *)mem) + hsize);
	mem->width = mem->height = 0;
	mem->width_max = border_width;
	mem->height_max = height - border_width * 2;
	mem_rect->mems[2] = mem;

	mem = (struct cavan_display_memory *)(((byte *)mem) + vsize);
	mem->width = mem->height = 0;
	mem->width_max = border_width;
	mem->height_max = height - border_width * 2;
	mem_rect->mems[3] = mem;

	mem_rect->width = width;
	mem_rect->height = height;
	mem_rect->border_width = border_width;

	return mem_rect;
}

int cavan_display_memory_rect_backup(struct cavan_display_device *display, struct cavan_display_memory_rect *mem_rect, int x, int y)
{
	unsigned int i;
	struct cavan_display_memory *mem;

	mem = mem_rect->mems[0];
	mem->x = x;
	mem->y = y;

	mem = mem_rect->mems[1];
	mem->x = x;
	mem->y = y + mem_rect->height - mem_rect->border_width;

	mem = mem_rect->mems[2];
	mem->x = x;
	mem->y = y + mem_rect->border_width;

	mem = mem_rect->mems[3];
	mem->x = x + mem_rect->width - mem_rect->border_width;
	mem->y = y + mem_rect->border_width;

	for (i = 0; i < NELEM(mem_rect->mems); i++)
	{
		int ret;

		mem = mem_rect->mems[i];
		mem->width = mem->width_max;
		mem->height = mem->height_max;

		ret = display->display_memory_xfer(display, mem, true);
		if (ret < 0)
		{
			pr_red_info("display->display_memory_xfer");
			return ret;
		}
	}

	mem_rect->x = x;
	mem_rect->y = y;

	return 0;
}

int cavan_display_memory_rect_restore(struct cavan_display_device *display, struct cavan_display_memory_rect *mem_rect)
{
	unsigned int i;

	for (i = 0; i < NELEM(mem_rect->mems); i++)
	{
		int ret;

		ret = display->display_memory_xfer(display, mem_rect->mems[i], false);
		if (ret < 0)
		{
			pr_red_info("display->display_memory_xfer");
			return ret;
		}
	}

	return 0;
}