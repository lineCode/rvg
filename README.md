# Retained vulkan/vector graphics

Vulkan library for high-level 2D vector-like rendering.
Modeled loosely after svg, inspired by nanoVG.
Uses retained mode for rendering which makes it highly efficient
for rendering with vulkan since curves and shapes are not recomputed
and uploaded every frame but just once. Does not even need a command buffer
rerecord every frame, even things like paints, shapes or transforms can be
changed without triggering the need for a command buffer rerecord which makes
it use way less cpu performance than immediate mode alternatives.
Could easily be used for a gui library.

## Roadmap

- [x] windows (basic panes, no operations)
- [x] widget sizing options, Window::create auto sizing
  - [x] auto sizing on construction
- [x] row layouts
- [x] slider
- [x] rvg: rounded rect
- [ ] more advanced textfield
  - [x] scrolling, clipping
  - [ ] enter/escape
  - [x] selection
  - [ ] some basic shortcuts like ctrl-a (might need ny fixes)
- [x] fix widget resizing todos
- [x] rvg: sanity checking (with asserts/logs)
  - [x] color functions, conversion
  - [x] shape drawing functions
- [x] rvg: antialiasing
  - [x] fix stroke caps
  - [x] better settings (Context, DrawMode)
  - [x] simplify Polygon
- [x] rvg: paint/transform/scissor on deviceLocal memory
  - [x] probably enough when specifiable on construction, must not be dynamic
  - [x] also text
  - [x] more efficient staging writes. Don't submit command buffer at once
    - [x] use semaphores (-> vpp: work chaining)
	      NOTE: abandoned the vpp work chaining concept, too high-level, cost
- [x] rvg: correct vulkan synchronization
  - [ ] probably best to require the user to set it in the render pass or
        otherwise handle it. Document this somewhere
- [x] better textures: use optimal layout, new context-based uploading cmdbuf
- [x] rvg: reorganize/split header/sources
  - [x] shapes/context/texture/transform/scissor headers
  - [x] separate path.hpp in separate library/utility
  - ~~ [ ] also make nk/font.h public header ~~ (bad idea)
  - [x] split sources (state/context/shapes/text/font)
- [ ] rvg::Context: use vpps new pipeline creation info
- [ ] rvg testing
	- [ ] lots of small unit tests, especially polygon, color conversion
	- [ ] integration tests, try to draw everything onto a framebuffer
	- [ ] especially test defined behaviour when moving/destructing
	      objects
- [x] vui: pane
- [ ] vui: row
- [ ] vui: non-drawing widgets (like row/column) should not create
      transform/scissor objects
- [ ] vui: don't make windows manage layouting. Make them (like panes) manage
      exactly one embedded widget which may be a layout widget
	  - [ ] implement real layout-only container widgets
- [ ] vui: validate styles passed to widgets (assert valid)
- [x] vui: improve/fix hacked together ColorButton
- [ ] rvg: make non-texture gradients make use of transform buffer span
- [ ] nanovg like box gradient
- [ ] readd vui::Slider (with (optional?) different style)
- [ ] implement vui cursor image callback in gui listener (e.g. textfield hover)
- [ ] vui: window scrolling
- [ ] vui: label
- [ ] vui: window names
- [ ] vui: horizontal splitting line
- [ ] clipboard support (probably over Gui/GuiListener)
- [ ] split rvg and vui library
- [ ] vui: radio button
- [ ] don't use that much paints and descriptors for widgets
  -> optional dynamic new ext descriptor support
  -> advanced styling/themes
- [ ] allow to specify fringe on context creation (?)
- [ ] widget styles, also spacings/paddings/margins/borders etc
- [ ] popups (needed for dropdown menu, tooltip)
- [x] z widget ordering
  - [ ] temporary raise on one layer (reorder in vector)
  - [ ] allow widgets to change it? needed?
- [ ] dropdown menu
- [ ] vui: performance optimziations #2
      - [ ] Especially don't call the size() function so often (in 
	        deriving hirachies: every constructor again)
	  - [ ] ColorButon pane hides/unhides too often
	  - [ ] Eliminate redundant construct/change calls of rvg shapes as
	        possible
- [ ] vui: runtime style changing
	- [ ] every widget has to implement support
	- [ ] also change the gui style, all widgets (that use those styles)
	      should update/be updated
- [ ] rvg: radial gradients
	- [ ] any other gradient types to implement?
- [x] tooltip (note: implement as vui::(Delayed)Hint)
- [x] FIX! rvg: currently undefined behaviour when destroying an objects at
	certain points: after updateDevice (cmd buf recording) and before
	the cmd buf is executed.
	- [ ] needs to be tested
- [ ] tabs (vui::TabbedPane or something as class)
- [ ] better mouse/keyboard grabs
  - [ ] currently bugs when multiple button grabs
  - [ ] key grabs (needed?)
- [x] think about dynamic scissor, avoiding rerecording on Widget::bounds
- [ ] benchmark alternative pipelines, optimize default use cases
  - [ ] performance optimizations, resolve performance todos
  - [ ] rvg: better with more (but also more optimized) pipelines?
- [ ] beautiful demos with screenshots
- [ ] multistop gradients (?), using small 1d textures
  - [ ] see discussion https://github.com/memononen/nanovg/pull/430
- [ ] release public version
- [ ] rvg: more stroke settings: linecap/linejoin [complex; -> katachi]
- [ ] window decorations/integrate with tabs
- [ ] animations
- [ ] advanced widget sizing hints, min/max size (needed?)
- [ ] textfields/slider combos for ints/floats
- [ ] better,easier custom navigation (e.g. tab-based)
- [ ] custom grabbing slider
- [ ] window operations (move, resize) (?)
- [ ] graph widget, e.g. for frametimes
- [ ] drag and drop stuff (not sure if needed at all)
- [ ] helper for non-convex shapes (in rvg: stencil buffer? or decomposition?)

- [ ] document stuff
  - [ ] intro tutorial, getting started

TODO(performance): use own BufferAllocator for staging buffer in context
  and clear all allocations on frame end. Also own DescriptorAllocator?
TODO(performance): use direct write for small updates in upload140?
TODO(performance): reduce number of SubBuffers? In text/polygon.
  will probably require the vpp::offset feature for upload140
