#pragma once

#include "ffmpeg.h"

#include "std.h"

namespace ffmpegcpp
{
	class FFmpegException : std::exception
	{

	public:

		FFmpegException(std::string error);

		FFmpegException(std::string error, int returnValue);

		virtual char const* what() const noexcept
		{
			return error_.c_str();
			//return std::exception::what();
		}


	private:
		std::string error_;
		//char error[AV_ERROR_MAX_STRING_SIZE];
	};
}