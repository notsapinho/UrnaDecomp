/* Keep-alive driver for the libqrencode probe: the one call the app makes into the library (target fn 5502, stub in
   api/gui/cqrcodeguard.cpp), QRcode_encodeString on a string with version 0, QR_ECLEVEL_L, QR_MODE_8 and case
   sensitivity, so binaryen inlines and keeps out of line what it does in the target (docs/reference/facts/libraries.md
   B10). */
#include <emscripten.h>
#include <stdlib.h>
#include "qrencode.h"

EMSCRIPTEN_KEEPALIVE int probe_qr(const char *s)
{
	QRcode *code;
	int w;

	code = QRcode_encodeString(s, 0, QR_ECLEVEL_L, QR_MODE_8, 1);
	if(code == NULL) return -1;
	w = code->width + code->data[0];
	QRcode_free(code);
	return w;
}
