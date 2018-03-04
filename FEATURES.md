
# ModestEx Features

## find
Get the descendants of each element in the current set of matched elements, filtered by a selector.

	iex> ModestEx.find("<p><a>Hello</a> World</p>", "p a")
	["<a>Hello</a>"]

	iex> ModestEx.find("<p><span>Hello</span> <span>World</span></p>", "span")
	["<span>Hello</span>", "<span>World</span>"]

## serialize
Serialize any string with valid or broken html and return a valid html string.

	iex> ModestEx.serialize("<div>Hello<span>World")
	"<html><head></head><body><div>Hello<span>World</span></div></body></html>"

## get_attribute

Get the value of an attribute for all elements in the set of matched elements.

	iex> ModestEx.get_attribute("<a href=\"https://elixir-lang.org\">Hello</a>", href")
	["https://elixir-lang.org"]

	iex> ModestEx.get_attribute("<p><a href=\"https://elixir-lang.org\">Hello</a></p>", "p a", "href")
	["https://elixir-lang.org"]

## set_attribute

Set one or more attributes for every matched element.

	iex> ModestEx.set_attribute("<a href=\"\">Hello</a>", href, "https://elixir-lang.org")
	"<html><head></head><body><a href=\"https://elixir-lang.org\">Hello</a></body></html>"

	iex> ModestEx.set_attribute("<p><a href=\"\">Hello</a></p>", "p a", "href", "https://elixir-lang.org")
	"<html><head></head><body><p><a href=\"https://elixir-lang.org\">Hello</a></p></body></html>"

	iex> ModestEx.set_attribute(["<p><a>Hello</a></p>", "<p><a>World</a></p>"], "p a", "href", ["https://elixir-lang.org", "https://google.de"])
	["<html><head></head><body><p><a href=\"https://elixir-lang.org\">Hello</a></p></body></html>", "<html><head></head><body><p><a href=\"https://google.de\">World</a></p></body></html>"]

## get_text
Get the combined text contents of each element in the set of matched elements, including their descendants.

	iex> ModestEx.get_text("<p><span><a>Hello</a></span><span><a>World</a></span></p>")
	["Hello", "World"]

	iex> ModestEx.get_text("<p><span><a>Hello</a></span><span><a>World</a></span></p>", "span a")
	["Hello", "World"]

## set_text
Set the content of each element in the set of matched elements to the specified text.

	iex> ModestEx.set_text("<p><span><a>Hello</a></span><span><a>Hello</a></span></p>", "a", "World")
	"<html><head></head><body><p><span><a>World</a></span><span><a>World</a></span></p></body></html>"
	
## prepend
Insert content, specified by the parameter, to the beginning of each element in the set of matched elements.

*in progress...*

## append
Insert content, specified by the parameter, to the end of each element in the set of matched elements.

*in progress...*

## insert_after
Insert every element in the set of matched elements after the target.

*in progress...*

## insert_before
Insert every element in the set of matched elements before the target.

*in progress...*

## remove
Remove the set of matched elements from the DOM.

*in progress...*