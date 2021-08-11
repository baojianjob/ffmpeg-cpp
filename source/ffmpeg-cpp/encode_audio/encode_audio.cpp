
#include <iostream>

#include "ffmpegcpp.h"

using namespace std;
using namespace ffmpegcpp;

class FileReader : public AVMemRead {
public:
  FileReader() { file_ptr_ = NULL; }
  ~FileReader() {
		if (file_ptr_ != NULL) {
		  fclose(file_ptr_);
		  file_ptr_ = NULL;
		}
  }

  bool Init(const char *filename) {
		file_ptr_ = fopen(filename, "rb");
		if (file_ptr_ == NULL) return false;
		return AVMemRead::Init() == 0;
  }

  virtual int ReadData(uint8_t *buf, int buf_size) { 
		size_t ret = fread(buf, 1, buf_size, file_ptr_); 
		if(ret == 0) return AVERROR_EOF;
		return ret;
  }

private:
  FILE *file_ptr_;
};

int main()
{
	// This example will take a raw audio file and encode it into as AAC.
	try
	{
		// Create a muxer that will output as AAC.
		const char *out_url = "output.flv";
		//const char *out_url = "rtmp://119.29.98.117/live/livestream";
		Muxer* muxer = new Muxer(out_url, "flv");

		// Create a AAC codec that will encode the raw data.
		AudioCodec* codec = new AudioCodec(AV_CODEC_ID_AAC);

		// Create an encoder that will encode the raw audio data as AAC.
		// Tie it to the muxer so it will be written to the file.
		AudioEncoder* encoder = new AudioEncoder(codec, muxer);

		// Load the raw audio file so we can process it.
		// We need to provide some info because we can't derive it from the raw format.
		// Hand it the encoder so it will pass on its raw data to the encoder, which will in turn pass it on to the muxer.
		//const char* rawAudioFile = "samples/Vivaldi_s16le_2_channels_samplerate_11025.dat";
		//const char* rawAudioFormat = "s16le"; int rawAudioSampleRate = 11025; int rawAudioChannels = 2;

		const char* rawAudioFile = "samples/people_s16le_44khz_c2.pcm";
		const char* rawAudioFormat = "s16le"; int rawAudioSampleRate = 44100; int rawAudioChannels = 2;

		//RawAudioFileSource* audioFile = new RawAudioFileSource(rawAudioFile, rawAudioFormat, rawAudioSampleRate, rawAudioChannels, encoder);

		FileReader *file_reader = new FileReader;
		if (!file_reader->Init(rawAudioFile)) return -1;
		RawAudioFileSource* audioFile = new RawAudioFileSource(file_reader, rawAudioFormat, rawAudioSampleRate, rawAudioChannels, encoder);

		// Prepare the output pipeline. This will push a small amount of frames to the file sink until it IsPrimed returns true.
		audioFile->PreparePipeline();

		// Push all the remaining frames through.
		while (!audioFile->IsDone())
		{
			audioFile->Step();
		}
		
		// Save everything to disk by closing the muxer.
		muxer->Close();
		delete file_reader;
	}
	catch (FFmpegException e)
	{
		cerr << "Exception caught!" << endl;
		cerr << e.what() << endl;
		throw e;
	}

	cout << "Encoding complete!" << endl;
	cout << "Press any key to continue..." << endl;

	getchar();
}
