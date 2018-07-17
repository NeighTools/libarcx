#include <string.h>
#include <zstd.h>
#include <lz4.h>

size_t decompress_data_lz4(void *input_buffer, size_t input_size, void *output_buffer,
	size_t output_size)
{
	return LZ4_decompress_safe(input_buffer, output_buffer, input_size, output_size);
}

size_t decompress_data_uncompressed(void *input_buffer, size_t input_size, void *output_buffer, size_t output_size)
{
	size_t final_size = input_size < output_size ? input_size : output_size;
	memcpy_s(output_buffer, final_size, input_buffer, final_size);
	return final_size;
}

ZSTD_DCtx *zstd_context = NULL;

size_t decompress_data_zstd(void *input_buffer, size_t input_size, void *output_buffer,
	size_t output_size)
{
	if (zstd_context == NULL)
		zstd_context = ZSTD_createDCtx();
	return ZSTD_decompressDCtx(zstd_context, output_buffer, output_size, input_buffer, input_size);
}

