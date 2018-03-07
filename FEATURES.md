
# ModestEx Features

## find
Get the descendants of each element in the current set of matched elements, filtered by a selector.

	iex> ModestEx.find("<p><a>Hello</a> World</p>", "p a")
	"<a>Hello</a>"

	iex> ModestEx.find("<p><span>Hello</span><span>World</span></p>", "span")
	["<span>Hello</span>", "<span>World</span>"]

## serialize
Serialize any string with valid or broken html and return a valid html string.
Use a custom scope to control serialization.

	iex> ModestEx.serialize("<div>Hello<span>World", :body_children)
	"<div>Hello<span>World</span></div>"

	iex> ModestEx.serialize("", :html)
	"<html><head></head><body></body></html>"
  
## get_attribute

Get the value of an attribute for all elements in the set of matched elements.

	iex> ModestEx.get_attribute("<a href=\"https://elixir-lang.org\">Hello</a>", href")
	"https://elixir-lang.org"

	iex> ModestEx.get_attribute("<p><a href=\"https://elixir-lang.org\">Hello</a></p>", "p a", "href")
	"https://elixir-lang.org"

## set_attribute

Set one or more attributes for every matched element.

	iex> ModestEx.set_attribute("<a href=\"\">Hello</a>", href, "https://elixir-lang.org")
	"<a href=\"https://elixir-lang.org\">Hello</a>"

	iex> ModestEx.set_attribute("<p><a href=\"\">Hello</a></p>", "p a", "href", "https://elixir-lang.org")
	"<p><a href=\"https://elixir-lang.org\">Hello</a></p>"

	iex> ModestEx.set_attribute(["<p><a>Hello</a></p>", "<p><a>World</a></p>"], "p a", "href", ["https://elixir-lang.org", "https://google.de"])
	["<p><a href=\"https://elixir-lang.org\">Hello</a></p>", "<p><a href=\"https://google.de\">World</a></p>"]

## get_text
Get the combined text contents of each element in the set of matched elements, including their descendants.

	iex> ModestEx.get_text("<p><span><a>Hello</a></span><span><a>World</a></span></p>")
	["Hello", "World"]

	iex> ModestEx.get_text("<p><span><a>Hello</a></span><span><a>World</a></span></p>", "span a")
	["Hello", "World"]

## set_text
Set the content of each element in the set of matched elements to the specified text.

	iex> ModestEx.set_text("<p><span><a>Hello</a></span><span><a>Hello</a></span></p>", "a", "World")
	"<p><span><a>World</a></span><span><a>World</a></span></p>"
	
## remove
Remove the set of matched elements from the html string.

	iex> ModestEx.remove("<div><p>Hello</p>World</div>", "div p")
	"<div>World</div>"

## append
Insert content, specified by the parameter, to the end of each element in the set of matched elements.

	iex> ModestEx.append("<div><p>Hello</p></div>", "div", "<p>World</p>")
	"<div><p>Hello</p><p>World</p></div>"

## prepend
Insert content, specified by the parameter, to the beginning of each element in the set of matched elements.

	iex> ModestEx.prepend("<div><p>World</p></div>", "div", "<p>Hello</p>")
	"<div><p>Hello</p><p>World</p></div>"

## insert_after
Insert every element in the set of matched elements after the target.

	iex> ModestEx.insert_after("<div><p>Hello</p></div>", "div p", "<p>World</p>")
	"<div><p>Hello</p><p>World</p></div>"

## insert_before
Insert every element in the set of matched elements before the target.

	iex> ModestEx.insert_before("<div><p>World</p></div>", "div p", "<p>Hello</p>")
	"<div><p>Hello</p><p>World</p></div>"

## replace
Replace each element in the set of matched elements with the provided new content and return the set of elements that was removed.

	iex> ModestEx.replace("<div><p>Hello</p></div>", "div p", "<p>World</p>")
	"<div><p>World</p></div>"

## slice
Slice set into two subsets. First set from first node until selected node. Second set from selected node to end.

*in progress...*
<!--
	iex> ModestEx.slice("<p>Hello</p><p>World</p>", "p:first-of_type")
	["<p>Hello</p>", "<p>World</p>"]
-->