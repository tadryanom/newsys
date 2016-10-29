/* Copyright (c) 2016, Piotr Durlej
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <wingui_color.h>
#include <wingui_form.h>
#include <wingui.h>

static void bargraph_redraw(struct gadget *g, int wd)
{
	win_color hi1, sh1;
	win_color hi2, sh2;
	win_color bg, fg;
	win_color bar;
	char buf[64];
	int tw0, th0;
	int tw1, th1;
	int w = 0;
	
	bg  = wc_get(WC_WIN_BG);
	fg  = wc_get(WC_WIN_FG);
	hi1 = wc_get(WC_HIGHLIGHT1);
	sh1 = wc_get(WC_SHADOW1);
	hi2 = wc_get(WC_HIGHLIGHT2);
	sh2 = wc_get(WC_SHADOW2);
	bar = fg;
	
	sprintf(buf, "%i", g->bargraph.limit);
	win_text_size(WIN_FONT_DEFAULT, &tw0, &th0, "0");
	win_text_size(WIN_FONT_DEFAULT, &tw1, &th1, buf);
	
	if (g->bargraph.limit > 0 && g->bargraph.value <= g->bargraph.limit)
	{
		w  = g->bargraph.value * (g->rect.w - tw1 - tw0 - 16);
		w /= g->bargraph.limit;
	}
	
	win_rect(wd,  bg,  0,		  0,		 g->rect.w, g->rect.h);
	win_rect(wd,  bar, tw0 + 5,	  4,		 w, g->rect.h - 8);
	win_hline(wd, sh1, 0,		  0,		 g->rect.w);
	win_hline(wd, hi1, 0,		  g->rect.h - 1, g->rect.w);
	win_vline(wd, sh1, 0,		  0,		 g->rect.h);
	win_vline(wd, hi1, g->rect.w - 1, 0,		 g->rect.h);
	win_hline(wd, sh2, 1,		  1,		 g->rect.w - 2);
	win_hline(wd, hi2, 1,		  g->rect.h - 2, g->rect.w - 2);
	win_vline(wd, sh2, 1,		  1,		 g->rect.h - 2);
	win_vline(wd, hi2, g->rect.w - 2, 1,		 g->rect.h - 2);
	
	win_text(wd, fg, 4,		      (g->rect.h - th0) / 2, "0");
	win_text(wd, fg, g->rect.w - tw1 - 4, (g->rect.h - th1) / 2, buf);
}

struct gadget *bargraph_creat(struct form *f, int x, int y, int w, int h)
{
	struct gadget *g;
	
	g = gadget_creat(f, x, y, w, h);
	if (g == NULL)
		return NULL;
	
	g->redraw = bargraph_redraw;
	g->bargraph.limit = 100;
	return g;
}

void bargraph_set_limit(struct gadget *g, int limit)
{
	g->bargraph.limit = limit;
	gadget_redraw(g);
}

void bargraph_set_value(struct gadget *g, int value)
{
	g->bargraph.value = value;
	gadget_redraw(g);
}