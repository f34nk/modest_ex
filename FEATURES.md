
# ModestEx Features

## find
Get the descendants of each element in the current set of matched elements, filtered by a selector.

	iex> ModestEx.find("<p><a>Hello</a> World</p>", "p a")
	{:ok, "<a>Hello</a>"}

	iex> ModestEx.find("<p><span>Hello</span> <span>World</span></p>", "span")
	{:ok, "<span>Hello</span>|<span>World</span>"}

	iex> ModestEx.find("<p><span>Hello</span> <span>World</span></p>", "span", "( ͡ᵔ ͜ʖ ͡ᵔ )")
	{:ok, "<span>Hello</span>( ͡ᵔ ͜ʖ ͡ᵔ )<span>World</span>"}



## serialize
Serialize any string with valid or broken html and return a valid html string.

	iex> ModestEx.serialize("<div>Hello<span>World")
	{:ok, "<html><head></head><body><div>Hello<span>World</span></div></body></html>"}



#### **Stay tuned for more...**

<!-- 
## remove
Remove the set of matched elements from the DOM.

	{:ok, html, removed} = ModestEx.remove(html, selector)

## appendTo
Insert every element in the set of matched elements to the end of the target.

	{:ok, html, appended} = ModestEx.appendTo(html, selector, new_html)

## replaceWith
Replace each element in the set of matched elements with the provided new content and return the set of elements that was removed.

	{:ok, html, replaced} = ModestEx.replaceWith(html, selector, new_html)

## prepend
Insert content, specified by the parameter, to the beginning of each element in the set of matched elements.

	{:ok, html, prepended} = ModestEx.prepend(html, selector, new_html)

## prependTo
Insert every element in the set of matched elements to the beginning of the target.
	
	{:ok, html, prepended} = ModestEx.prependTo(html, selector, new_html)

## slice
Reduce the set of matched elements to a subset specified by a range of indices.

	{:ok, slices} = ModestEx.slice(html, start_selector, end_selector)

.slice( start [, end ] )
https://api.jquery.com/slice/ -->