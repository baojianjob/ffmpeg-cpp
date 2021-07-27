#include "FFmpegException.h"

using namespace std;

namespace ffmpegcpp
{
	FFmpegException::FFmpegException(string error) : exception()
	{
		error_ = error;
	}

	FFmpegException::FFmpegException(string error, int returnValue)
		: exception()
	{
		char error_buf[AV_ERROR_MAX_STRING_SIZE] = { 0 };
		av_make_error_string(error_buf, AV_ERROR_MAX_STRING_SIZE, returnValue);
		error_ = error;
		error_ += ": ";
		error_ += error_buf;
	}
}