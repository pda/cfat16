# Monitor files for changes, trigger events.
# More info at https://github.com/guard/guard#readme

guard :shell do
  watch("Makefile") { `make clean` }
  watch(%r{\.[ch]}) { `(make && ./read_fat); date` }
end
