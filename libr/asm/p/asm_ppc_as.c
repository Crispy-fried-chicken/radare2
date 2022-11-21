/* radare - LGPL - Copyright 2020-2022 eagleoflqj */

#include <r_lib.h>
#include "../binutils_as.h"

#define ASSEMBLER "R2_PPC_AS"

static int assemble(RAsm *a, RAsmOp *op, const char *buf) {
#if __powerpc__
	char *as = "as";
#else
	char *as = "";
#endif
	char *opts = r_str_newf ("-mregnames -a%d %s", a->config->bits,
		R_ARCH_CONFIG_IS_BIG_ENDIAN (a->config) ? "-be" : "-le");
	return binutils_encode (a, op, buf, as, ASSEMBLER, "", opts);
}

RAsmPlugin r_asm_plugin_ppc_as = {
	.name = "ppc.as",
	.desc = "as PPC Assembler (use "ASSEMBLER" environment)",
	.arch = "ppc",
	.author = "eagleoflqj",
	.license = "LGPL3",
	.bits = 32 | 64,
	.endian = R_SYS_ENDIAN_LITTLE | R_SYS_ENDIAN_BIG,
// 	.encode = &encode,
};

#ifndef R2_PLUGIN_INCORE
R_API RLibStruct radare_plugin = {
	.type = R_LIB_TYPE_ASM,
	.data = &r_asm_plugin_ppc_as,
	.version = R2_VERSION
};
#endif
