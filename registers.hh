#pragma once

register struct {
	union {
		struct {
			u8 f;
			u8 a;
		};
		u16 af;
	};

	union {
		struct {
			u8 c;
			u8 b;
		};
		u16 bc;
	};

	union {
		struct {
			u8 e;
			u8 d;
		};
		u16 de;
	};

	union {
		struct {
			u8 l;
			u8 h;
		};
		u16 hl;
	};
} reg asm("r12");

struct {
	bool z;
	bool n;
	bool h;
	bool c;
} flags;

u16 sp;
