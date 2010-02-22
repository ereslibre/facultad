PL = pl

all: fibonacci

fibonacci: fibonacci.pl
	$(PL) -q -t main -o $@ -c $@.pl

clean:
	rm -f fibonacci
