Grep-Notify
===========

Reads stdout from a program and `notify-send` whole line if the regex matches.

Example:

    $ cat file
    I am a line
    I am a line too!
    $ cat file | grep-notify too
    I am a line
    I am a line too!
    # => 'I am a line too!' is sent
