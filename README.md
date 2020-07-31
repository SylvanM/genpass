# genpass

`genpass` is a command line tool that will generate random passwords and random numbers for you using Apple's cryptographically secure random number generator.

## Usage

### Generating random passwords

The character set used by `genpass` is 7-bit ASCII, without any control characters.

To generate a random password, just run

```bash
genpass
```

with no arguments. This will give you a random password of 16 characters.

Passing a number parameter after the call to `genpass` will tell `genpass` how long to make the password. For example, to generate a 32 character password, run

```bash
genpass 32
```

Some websites do not allow certain characters in their passwords. To account for this, `genpass` can exclude characters you tell it to. This can be done with the `-x` or `--except` flag.
If I want to exclude `!`, `_`, and `\`, I would give all forbidden characters in a single argument:

```bash
genpass -x !_\
```

If you want to specify the length of the password as well as forbidden characters, specify the length **before** the illegal characters:

```bash
genpass 12 !@#/? # generates a random 12 character password without a !, @, #, /, or ? in it.
```

### Generating random numbers 

To generate a random number, pass either `-n` or `--number` to `genpass

```bash
genpass -n
```

and it will generate a number that can fit into one word on your machine. For most modern computers, this is 64 bits, so you will get a number between 0 and 2^64 - 1, inclusive.

If you want, you can specify a range for the random number:

```bash
genpass -n 1 1000 # generates a random number between 1 and 1000, inclusive
```

