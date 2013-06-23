#!/bin/bash
# http://electron.mit.edu/~gsteele/ffmpeg/
# http://www.ehow.com/how_7211144_make-gif-animation-linux.html
echo "Converting ppm images to jpg"
for f in *ppm ; do convert -quality 100 $f `basename $f ppm`jpg; done
echo "Creating avi from jpg sequence"
mencoder "mf://*.jpg" -mf fps=25 -o video.avi -ovc lavc -lavcopts vcodec=msmpeg4v2:vbitrate=8000
echo "Creating ogv from avi"
ffmpeg2theora -i video.avi -o video.ogg -v 10
echo "Creating gif from jpg sequence"
convert -delay 4 -loop 0 *.jpg video.gif
echo "Done"
