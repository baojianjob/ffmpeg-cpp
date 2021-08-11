#pragma once

#include "ffmpeg.h"

#include "InputSource.h"
#include "Demuxer.h"


namespace ffmpegcpp
{
	class AVMemIO {
	public:
		AVMemIO() {
			avio_contex_ = NULL;
			io_buffer_ = NULL;
		}

		virtual ~AVMemIO() {
			if (avio_contex_) av_freep(&avio_contex_->buffer);
			avio_context_free(&avio_contex_);
		}

		public:
		AVIOContext *avio_contex_;
		uint8_t *io_buffer_;
	};

	class AVMemRead : public AVMemIO {
	public:
		int Init(size_t init_buf_size = 4096) {
			io_buffer_ = (uint8_t *)av_malloc(init_buf_size);
			if (io_buffer_ == NULL) return AVERROR(ENOMEM);

			avio_contex_ = avio_alloc_context(io_buffer_, (int)init_buf_size, 0, this, &AVMemRead::ReadData, NULL, NULL);
			if (io_buffer_ == NULL) return AVERROR(ENOMEM);
			return 0;
		}

		static int ReadData(void *opaque, uint8_t *buf, int buf_size) {
			AVMemRead *this_ptr = (AVMemRead *)opaque;
			return this_ptr->ReadData(buf, buf_size);
		}

		virtual int ReadData(uint8_t *buf, int buf_size) = 0;

		friend class Demuxer;
	};

	class RawAudioFileSource : public InputSource
	{
	public:

		RawAudioFileSource(const char* fileName, const char* inputFormat, int sampleRate, int channels, FrameSink* frameSink);
		RawAudioFileSource(AVMemRead *mem_read, const char* inputFormat, int sampleRate, int channels, FrameSink* frameSink);
		virtual ~RawAudioFileSource();

		virtual void PreparePipeline();
		virtual bool IsDone();
		virtual void Step();

	private:

		void CleanUp();

		Demuxer* demuxer = nullptr;
	};


}
