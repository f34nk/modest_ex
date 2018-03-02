
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

	iex> ModestEx.set_attribute("<p><a>Hello</a><a>World</a></p>", "p a", "href", ["https://elixir-lang.org", "https://google.de"])
	"<html><head></head><body><p><a href=\"https://elixir-lang.org\">Hello</a><a href=\"https://google.de\">World</a></p></body></html>"

#### **Stay tuned for more...**