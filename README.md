Grep-Notify
===========

```
Usage: grep-notify [-k] [-u URGENCY] PATTERN [TITLE]

DESCRIPTION
  grep-notify searches for PATTERN from STDIN and sends a notification
  whenever it's matched.  If no TITLE is given, the notification title
  is 'Grep Notify'.

OPTIONS
  -k Keep the original program STDOUT
  -u Set the urgency to low|normal|critical. Default: normal.
```

## Examples

    $ cat file
    I am a line
    I am a line too!
    I am the line two!

    $ cat file | grep-notify too
    I am a line too!
    # => 'I am a line too!' is sent

    $ cat file | grep-notify t.o
    I am a line too!
    I am the line two!
    # => 'I am a line too!'   is sent
    # => 'I am the line two!' is sent

    $ cat file | grep-notify -k t.o
    I am a line
    I am a line too!
    I am the line two!
    # => 'I am a line too!'   is sent
    # => 'I am the line two!' is sent
