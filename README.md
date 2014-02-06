rdf-numbers
===========

RDF generator for numbers.

This program generates large quantities of (hopefully good) RDF for
testing scalability.

To build, just type 'make'.  This builds two programs: numgen and test.

"test" is used to determine that the internal functions are all working as
expected.  It is only included for completeness.

"numgen" will generate RDF describing numbers up to 2^32 or to a number
provided on the command line.  The RDF is sent to stdout.  I advise piping the
results through gzip.

The properties described are:
 * An english textual representation of the number
 * The Roman numeral representation for the number, if it is less than 40000
 * Whether or not the number is prime
 * The list of prime factors for the number
 * The square of the number (for all numbers whose square is less than 2^32)
 * Whether or not the number is triangular
 * Whether or not the number is Perfect

When run, the numgen program will start by generating an internal list of all
prime numbers to 2^32.  This process can take some time.  Once this list is
built, the program will start generating the RDF.

The process is less than optimal, and Generating this much RDF takes a long
time.  In order to terminate the generation cleanly, send a USR1 signal to the
application.
eg.
```bash
"killall -USR1 numgen"
```

Terminating early will finish writing the properties for the current number,
and write the correct XML tags to indicate the end of the document.

