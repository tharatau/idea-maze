patch:
	chmod 755 ./scripts/patch
	bash ./scripts/patch

split:
	splitdiff -a -p 2 -d -D ./patches/latest/chromium ./patches/0.73.x/chromium.patch
	splitdiff -a -p 2 -d -D ./patches/latest/node ./patches/0.73.x/node.patch
	splitdiff -a -p 2 -d -D ./patches/latest/v8 ./patches/0.73.x/v8.patch

build:
	chmod 755 ./scripts/build
	bash ./scripts/build