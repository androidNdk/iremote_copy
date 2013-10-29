/**
 * Copyright (c) 2013 Egor Pushkin. All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef MIXERVOLUMECONTROL_H__REMOTEPC__INCLUDED_
#define MIXERVOLUMECONTROL_H__REMOTEPC__INCLUDED_

namespace RemotePC
{

	class MixerVolumeControl 
		: public mc::CommonImpl< IVolumeControl >
		, public mc::CommonImpl< IVolumeControlInitializer >
	{
	public:

		typedef mc::CommonImpl< IVolumeControl > ClassRoot_;

		MixerVolumeControl();
		virtual ~MixerVolumeControl();

	public:

		// IVolumeControlInitializer section
		virtual mc::result Initialize(HWND hwnd);

		// IVolumeControl section
		virtual mc::result GetVolume(double &volume) const;

		virtual mc::result SetVolume(double volume) const;

		virtual mc::result GetNormalizedVolume(unsigned long &volume) const;

		virtual mc::result SetNormalizedVolume(unsigned long volume) const;

		virtual double GetMinimumVolume() const;

		virtual double GetMaximumVolume() const;
		
	private:	

		mc::result OpenMixer(HWND hwnd);

		mc::result GetMasterControl();

		mc::result GetVolumeInternal(double &volume) const;

		mc::result SetVolumeInternal(double volume) const;
		
	private:

		HMIXER mixer_;
		MIXERCAPS mixerCaps_;
		DWORD volumeControl_;
		DWORD minimumVolume_;
		DWORD maximumVolume_;

	};

}

#endif // MIXERVOLUMECONTROL_H__REMOTEPC__INCLUDED_
