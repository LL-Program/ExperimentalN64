/* Copyright (c) 2020 Themaister
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef LOAD_TRIANGLE_SETUP_H_
#define LOAD_TRIANGLE_SETUP_H_

TriangleSetup load_triangle_setup(uint index)
{
#if SMALL_TYPES
	return triangle_setup.elems[index];
#else
	return TriangleSetup(
			triangle_setup.elems[index].xh,
			triangle_setup.elems[index].xm,
			triangle_setup.elems[index].xl,
			i16(triangle_setup.elems[index].yh),
			i16(triangle_setup.elems[index].ym),
			triangle_setup.elems[index].dxhdy,
			triangle_setup.elems[index].dxmdy,
			triangle_setup.elems[index].dxldy,
			i16(triangle_setup.elems[index].yl),
			u8(triangle_setup.elems[index].flags),
			u8(triangle_setup.elems[index].tile));
#endif
}

#endif