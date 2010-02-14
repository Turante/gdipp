#pragma once

#include "global.h"
#include <vector>
using namespace std;

class _gdimm_text
{
	// device context attributes
	HDC _hdc_text;
	POINT _cursor;
	BOOL _update_cursor;
	UINT _text_alignment;
	int _char_extra;
	RGBQUAD _fg_rgb;
	COLORREF _bg_color;

	// metrics
	BYTE *_metric_buf;
	OUTLINETEXTMETRIC *_outline_metrics;
	LOGFONT _font_attr;

	//misc
	UINT _eto_options;

	static int get_ft_bmp_width(const FT_Bitmap &bitmap);
	static void draw_background(HDC hdc, const RECT *bg_rect, COLORREF bg_color);
	int get_dc_bpp() const;
	FT_Render_Mode get_render_mode(WORD dc_bpp) const;
	bool get_dc_metrics();
	void get_glyph_clazz();
	FT_BitmapGlyph get_glyph_bmp(
		WCHAR ch,
		UINT ggo_format,
		const MAT2 &matrix,
		FT_Render_Mode render_mode,
		GLYPHMETRICS &glyph_metrics) const;
	void set_bmp_bits_mono(
		const FT_Bitmap &src_bitmap,
		int x_in_dest, int y_in_dest,
		BYTE *dest_bits,
		int dest_width, int dest_height,
		bool is_dest_up,
		WORD dest_bpp) const;
	void set_bmp_bits_gray(
		const FT_Bitmap &src_bitmap,
		int x_in_dest, int y_in_dest,
		BYTE *dest_bits,
		int dest_width, int dest_height,
		bool is_dest_up,
		WORD dest_bpp) const;
	void set_bmp_bits_lcd(
		const FT_Bitmap &src_bitmap,
		int x_in_dest, int y_in_dest,
		BYTE *dest_bits,
		int dest_width, int dest_height,
		bool is_dest_up,
		WORD dest_bpp) const;
	bool draw_glyphs(
		const vector<FT_BitmapGlyph> &glyphs,
		const vector<POINT> &glyph_pos,
		CONST RECT *lprect,
		int dc_bpp) const;

	const TCHAR *get_family_name() const;
	const TCHAR *get_full_name() const;

public:
	_gdimm_text();
	~_gdimm_text();
	bool init(HDC hdc, int x, int y, UINT options);
	bool to_glyph_indices(LPCWSTR text, unsigned int count, WORD *glyph_indices);
	bool text_out(const WCHAR *string, unsigned int count, CONST RECT *lprect, CONST INT *lpDx);
};

typedef singleton<_gdimm_text> gdimm_text;