// Reveal.js configuration
// This file is automatically included by the cloudogu/reveal.js-docker image
// when mounted to /resources in the container

Reveal.initialize({
	// Display controls in the bottom right corner
	controls: true,

	// Display a presentation progress bar
	progress: true,

	// Display the page number of the current slide
	slideNumber: false,

	// Push each slide change to the browser history
	history: false,

	// Enable keyboard shortcuts for navigation
	keyboard: true,

	// Enable the slide overview mode
	overview: true,

	// Vertical centering of slides
	center: true,

	// Enables touch navigation on devices with touch input
	touch: true,

	// Loop the presentation
	loop: false,

	// Change the presentation direction to be RTL
	rtl: false,

	// Randomizes the order of slides each time the presentation loads
	shuffle: false,

	// Turns fragments on and off globally
	fragments: true,

	// Flags if we should show a help overlay when the questionmark
	// key is pressed
	help: true,

	// Flags if speaker notes should be visible to all viewers
	showNotes: false,

	// Global override for autoplaying embedded media (video/audio/iframe)
	// - null: Media will only autoplay if data-autoplay is present
	// - true: All media will autoplay, regardless of individual setting
	// - false: No media will autoplay, regardless of individual setting
	autoPlayMedia: null,

	// Number of milliseconds between automatically proceeding to the
	// next slide, disabled when set to 0, this value can be overwritten
	// by using a data-autoslide attribute on your slides
	autoSlide: 0,

	// Stop auto-sliding after user input
	autoSlideStoppable: true,

	// Use this method for navigation when arrows are clicked
	defaultTiming: null,

	// Enable slide navigation via mouse wheel
	mouseWheel: false,

	// Apply a 3D roll to links on hover
	rollingLinks: false,

	// Transition style
	transition: 'none', // none/fade/slide/convex/concave/zoom

	// Transition speed
	transitionSpeed: 'default', // default/fast/slow

	// Transition style for full page slide backgrounds
	backgroundTransition: 'fade', // none/fade/slide/convex/concave/zoom

	// The maximum number of pages a single slide can expand onto when printing
	// to PDF, unlimited by default
	pdfMaxPagesPerSlide: Number.POSITIVE_INFINITY,

	// Number of slides away from the current that are visible
	viewDistance: 3,

	// The display mode that will be used to show slides
	display: 'block',

	// Parallax scrolling
	parallaxBackgroundImage: '',
	parallaxBackgroundSize: '',

	// Number of pixels to move the parallax background per slide
	parallaxBackgroundHorizontal: null,
	parallaxBackgroundVertical: null,

	// The "normal" size of the presentation, aspect ratio will be preserved
	// when the presentation is scaled to fit different resolutions. Can be
	// specified using percentage units.
	width: 960,
	height: 700,

	// Factor of the display size that should remain empty around the content
	margin: 0.1,

	// Bounds for smallest/largest possible scale to apply to content
	minScale: 0.2,
	maxScale: 1.5,

	// Add any other reveal.js configuration options here
});

