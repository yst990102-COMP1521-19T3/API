# hack to cope with not wanting to expose Python source
ACTIVITY=cowrie
DIR=../../../private/activities/$(ACTIVITY)/solutions/python/
REFERENCE_IMPLEMENTATION_PYTHON=$(DIR)/$(ACTIVITY).py
REFERENCE_IMPLEMENTATION_PYC=$(DIR)/__pycache__/$(ACTIVITY).cpython-*.pyc

all: cowrie_reference_implementation chmod

chmod:
	chmod 755 test_bin/*

cowrie_reference_implementation: $(REFERENCE_IMPLEMENTATION_PYTHON)
	rm -rf __pycache__ *.pyc
	echo 'import py_compile;py_compile.compile("$(REFERENCE_IMPLEMENTATION_PYTHON)")'|python3 
	cp -p $(REFERENCE_IMPLEMENTATION_PYC) $(ACTIVITY)_reference_implementation
	chmod 755 $(ACTIVITY)_reference_implementation
