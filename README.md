Grep-Notify
===========

Reads from stdout and `notify-send` lines matched with `regex.h`

Example:

    $ cat file
    I am a line
    I am a line too!
    $ cat file | grep-notify too
    I am a line
    I am a line too!
    # => 'I am a line too!' is sent
