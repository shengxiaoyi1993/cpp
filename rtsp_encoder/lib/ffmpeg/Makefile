FFMPEG_FILE=ffmpeg-2.8.15.zip
FFMPEG_PATH=ffmpeg-2.8.15

all:
	# wget ftp://pub:9900@192.168.1.238/software/src/$(FFMPEG_FILE) -O $(FFMPEG_FILE)
	unzip -o $(FFMPEG_FILE)
	cd $(FFMPEG_PATH) && ./configure --enable-shared --disable-yasm && make -j4
	cp $(FFMPEG_PATH)/*/*.so.* ./so/ -rf
