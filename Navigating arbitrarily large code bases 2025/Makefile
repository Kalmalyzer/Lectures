
.PHONY: dev prod

dev:
	# Development mode (with live reloading for editing the slides)
	docker run --rm \
		-v "$(shell pwd)/docs/slides:/reveal/docs/slides" \
		-v "$(shell pwd)/scripts/test:/resources" \
		-e TITLE='Navigating arbitrarily large code bases' -e THEME_CSS='cloudogu-black.css' \
		-p 8000:8000 -p 35729:35729 \
		cloudogu/reveal.js:dev

prod:
	# Production Mode (smaller, more secure, just a static HTML site served by NGINX)
	docker run --rm \
		-v "$(shell pwd)/docs/slides:/reveal/docs/slides" \
		-v "$(shell pwd)/scripts/test:/resources" \
		-v "$(shell pwd)/x:/x" \
		-e TITLE='Navigating arbitrarily large code bases' -e THEME_CSS='cloudogu-black.css' \
		-p 8080:8080 \
		cloudogu/reveal.js
