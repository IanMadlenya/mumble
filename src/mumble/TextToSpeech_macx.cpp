/* Copyright (C) 2007, Sebastian Schlingmann <mit_service@users.sourceforge.net>

   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.
   - Neither the name of the Mumble Developers nor the names of its
     contributors may be used to endorse or promote products derived from this
     software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "TextToSpeech.h"
#include "Global.h"

/* need the undef or else the include would not work
 it would help to include the header before QT, but that might mess with QT */
#undef qDebug
#include "ApplicationServices/ApplicationServices.h"

class TextToSpeechPrivate {
	private:
		SpeechChannel speechchan;
	public:
		TextToSpeechPrivate();
		~TextToSpeechPrivate();
		void say(QString text);
		void setVolume(int v);
};

TextToSpeechPrivate::TextToSpeechPrivate() {
	NewSpeechChannel(NULL, &speechchan);
}

TextToSpeechPrivate::~TextToSpeechPrivate() {
	DisposeSpeechChannel(speechchan);
}

void TextToSpeechPrivate::say(QString text) {
	QByteArray ba = text.toUtf8();
	const char* val = ba.data();
	SpeakText(speechchan, val, 11);
}

void TextToSpeechPrivate::setVolume(int) {
}

TextToSpeech::TextToSpeech(QObject *p) : QObject(p) {
	enabled = true;
	d = new TextToSpeechPrivate();
}

TextToSpeech::~TextToSpeech() {
	delete d;
}

void TextToSpeech::say(QString text) {
	if (enabled)
		d->say(text);
}

void TextToSpeech::setEnabled(bool e) {
	enabled = e;
}

void TextToSpeech::setVolume(int volume) {
	d->setVolume(volume);
}


bool TextToSpeech::isEnabled() const {
	return enabled;
}
