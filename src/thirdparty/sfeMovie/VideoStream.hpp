
/*
 *  VideoStream.hpp
 *  sfeMovie project
 *
 *  Copyright (C) 2010-2014 Lucas Soltic
 *  lucas.soltic@orange.fr
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */

#ifndef SFEMOVIE_VIDEOSTREAM_HPP
#define SFEMOVIE_VIDEOSTREAM_HPP

#include "Macros.hpp"
#include "Stream.hpp"
#include <SFML/Graphics.hpp>
#include <stdint.h>

namespace sfe {
	class VideoStream : public Stream {
	public:
		struct Delegate {
			virtual void didUpdateImage(const VideoStream& sender, const sf::Texture& image) = 0;
		};
		
		/** Create a video stream from the given FFmpeg stream
		 *
		 * At the end of the constructor, the stream is guaranteed
		 * to have all of its fields set and the decoder loaded
		 */
		VideoStream(AVFormatContext* formatCtx, AVStream* stream, DataSource& dataSource, Timer& timer, Delegate& delegate);
		
		/** Default destructor
		 */
		virtual ~VideoStream();
		
		/** Get the stream kind (either audio, video or subtitle stream)
		 *
		 * @return the kind of stream represented by this stream
		 */
		virtual MediaType getStreamKind() const;
		
		/** Get the video frame size (width, height)
		 *
		 * @return the video frame size
		 */
		sf::Vector2i getFrameSize() const;
		
		/** Get the average amount of video frame per second for this stream
		 *
		 * @param formatCtx the FFmpeg format context to which this stream belongs
		 * @return the average framerate
		 */
		float getFrameRate() const;
		
		/** Get the SFML texture that contains the latest video frame
		 */
		sf::Texture& getVideoTexture();
		
		/** Update the video frame and the stream's status
		 */
		virtual void update();
	private:
		bool onGetData(sf::Texture& texture);
		
		/** Returns the difference between the video stream timer and the reference timer
		 *
		 * A positive value means the video stream is ahead of the reference timer
		 * whereas a nevatige value means the video stream is late
		 */
		sf::Time getSynchronizationGap();
		
		/** Decode the encoded data @a packet into @a outputFrame
		 *
		 * gotFrame being set to false means that decoding should still continue:
		 *  - with a new packet if false is returned
		 *	- with the same packet if true is returned
		 *
		 * @param packet the encoded data
		 * @param outputFrame one decoded data
		 * @param gotFrame set to true if a frame has been extracted to outputFrame, false otherwise
		 * @param goOn set to true if decoding can continue, or false if no more data can be decoded (EOF)
		 * @return true if decoding succeeded, false otherwise (EOF)
		 */
		bool decodePacket(AVPacket* packet, AVFrame* outputFrame, bool& gotFrame, bool& needsMoreDecoding);
		
		/** Initialize the audio resampler for conversion from many formats to signed 16 bits audio
		 *
		 * This must be called before any packet is decoded and resampled
		 */
		void initRescaler();
		
		/** Convert the decoded video frame @a frame into RGBA image data
		 *
		 * @param frame the audio samples to convert
		 * @param outSamples [out] the convertedSamples
		 * @param outNbSamples [out] the count of samples in @a outSamples
		 * @param outSamplesLength [out] the length of @a outSamples in bytes
		 */
		void rescale(AVFrame* frame, uint8_t* outVideoBuffer[4], int outVideoLinesize[4]);
		
		/** Load packets until one frame can be decoded
		 */
		void preload();
		
		// Timer::Observer interface
		void willPlay(const Timer &timer);
		
		// Private data
		sf::Texture m_texture;
		AVFrame* m_rawVideoFrame;
		uint8_t *m_rgbaVideoBuffer[4];
		int m_rgbaVideoLinesize[4];
		Delegate& m_delegate;
		
		// Rescaler data
		struct SwsContext *m_swsCtx;
		
		sf::Time m_lastDecodedTimestamp;
	};
}

#endif
