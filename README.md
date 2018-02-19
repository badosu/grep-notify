Grep-Notify
===========

Reads from stdout and `notify-send` lines matched with `regex.h`

Example:

    $ cat file
    I am a line
    I am a line too!
    I am the line two!
    
    $ cat file | grep-notify too
    # => 'I am a line too!' is sent
    
    $ cat file | grep-notify t.o
    # => 'I am a line too!'   is sent
    # => 'I am the line two!' is sent

    # You can also choose the title of the notification
    $ cat file | grep-notify too 'Grepped Program'
    # => 'I am a line too!' is sent with 'Grepped Program' title
