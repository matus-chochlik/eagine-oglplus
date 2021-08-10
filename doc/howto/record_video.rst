========================
Recording window content
========================

Ubuntu (recordmydesktop)
------------------------

Install the `recordmydesktop` and `ffmpeg` package:

::

  sudo apt install recordmydesktop ffmpeg


Open window to be recorded and get window id (by running the following command
and clicking on the target window):

::

  xwininfo | grep 'id: 0x'


Start recording the content of the target window by running, with the window id
obtained by the previous command:

::

  recordmydesktop --windowid 0x12345678 --fps 15 --no-sound


The recording can be stopped by sending the `SIGINT` signal to `recordmydesktop`
(for example by Ctrl+C in the terminal). By default a file called `out.ogv`
is created.

This file can be converted to the `gif` format with `ffmpeg` (in this case
also limiting the output file size to 14.5MB):

::

  ffmpeg -y -i out.ogv -fs 14500000 -r 15 out.gif
