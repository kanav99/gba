#pragma once

struct registers_t {
	struct {
		union {
			struct {
				unsigned char f;
				unsigned char a;
			};
			unsigned short af;
		};
	};
	
	struct {
		union {
			struct {
				unsigned char c;
				unsigned char b;
			};
			unsigned short bc;
		};
	};
	
	struct {
		union {
			struct {
				unsigned char e;
				unsigned char d;
			};
			unsigned short de;
		};
	};
	
	struct {
		union {
			struct {
				unsigned char l;
				unsigned char h;
			};
			unsigned short hl;
		};
	};
	
	unsigned short sp;
	unsigned short pc;
	bool flag_z;
	bool flag_n;
	bool flag_h;
	bool flag_c;
};
