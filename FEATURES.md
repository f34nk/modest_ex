
# ModestEx Features

## find
Get the descendants of each element in the current set of matched elements, filtered by a selector.

```elixir
iex> ModestEx.find("<p><a>Hello</a> World</p>", "p a")
"<a>Hello</a>"

iex> ModestEx.find("<p><span>Hello</span><span>World</span></p>", "span")
["<span>Hello</span>", "<span>World</span>"]
```

## serialize
Serialize any string with valid or broken html and return a valid html string.
Use a custom scope to control serialization.

```elixir
iex> ModestEx.serialize("<div>Hello<span>World", :body_children)
"<div>Hello<span>World</span></div>"

iex> ModestEx.serialize("", :html)
"<html><head></head><body></body></html>"
``` 

## get_attribute
Get the value of an attribute for all elements in the set of matched elements.

```elixir
iex> ModestEx.get_attribute("<a href=\"https://elixir-lang.org\">Hello</a>", "href")
"https://elixir-lang.org"

iex> ModestEx.get_attribute("<p><a href=\"https://elixir-lang.org\">Hello</a></p>", "p a", "href")
"https://elixir-lang.org"
```

## set_attribute
Set one or more attributes for every matched element.

```elixir
iex> ModestEx.set_attribute("<a href=\"\">Hello</a>", "href", "https://elixir-lang.org")
"<a href=\"https://elixir-lang.org\">Hello</a>"

iex> ModestEx.set_attribute("<p><a href=\"\">Hello</a></p>", "p a", "href", "https://elixir-lang.org")
"<p><a href=\"https://elixir-lang.org\">Hello</a></p>"

iex> ModestEx.set_attribute(["<p><a>Hello</a></p>", "<p><a>World</a></p>"], "p a", "href", ["https://elixir-lang.org", "https://google.de"])
["<p><a href=\"https://elixir-lang.org\">Hello</a></p>", "<p><a href=\"https://google.de\">World</a></p>"]
```

## get_text
Get the combined text contents of each element in the set of matched elements, including their descendants.

```elixir
iex> ModestEx.get_text("<p><span><a>Hello</a></span><span><a>World</a></span></p>")
["Hello", "World"]

iex> ModestEx.get_text("<p><span><a>Hello</a></span><span><a>World</a></span></p>", "span a")
["Hello", "World"]
```

## set_text
Set the content of each element in the set of matched elements to the specified text.

```elixir
iex> ModestEx.set_text("<p><span><a>Hello</a></span><span><a>Hello</a></span></p>", "a", "World")
"<p><span><a>World</a></span><span><a>World</a></span></p>"
```

## remove
Remove the set of matched elements from the html string.

```elixir
iex> ModestEx.remove("<div><p>Hello</p>World</div>", "div p")
"<div>World</div>"
```

## append
Insert content, specified by the parameter, to the end of each element in the set of matched elements.

```elixir
iex> ModestEx.append("<div><p>Hello</p></div>", "div", "<p>World</p>")
"<div><p>Hello</p><p>World</p></div>"
```

## prepend
Insert content, specified by the parameter, to the beginning of each element in the set of matched elements.

```elixir
iex> ModestEx.prepend("<div><p>World</p></div>", "div", "<p>Hello</p>")
"<div><p>Hello</p><p>World</p></div>"
```

## insert_after
Insert every element in the set of matched elements after the target.

```elixir
iex> ModestEx.insert_after("<div><p>Hello</p></div>", "div p", "<p>World</p>")
"<div><p>Hello</p><p>World</p></div>"
```

## insert_before
Insert every element in the set of matched elements before the target.

```elixir
iex> ModestEx.insert_before("<div><p>World</p></div>", "div p", "<p>Hello</p>")
"<div><p>Hello</p><p>World</p></div>"
```

## replace
Replace each element in the set of matched elements with the provided new content and return the set of elements that was removed.

```elixir
iex> ModestEx.replace("<div><p>Hello</p></div>", "div p", "<p>World</p>")
"<div><p>World</p></div>"
```

## slice
Reduce the set of matched elements to a subset specified by a range of indices.

```elixir
iex> ModestEx.slice("<h1>Lorem ipsum</h1><p>dolor sit amet</p><ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul><p>Sed ut perspiciatis</p><p>unde omnis iste natus</p>", "> *", 0, -1)
["<h1>Lorem ipsum</h1>", "<p>dolor sit amet</p>", "<ul><li>Coffee</li><li>Tea</li><li>Milk</li></ul>", "<p>Sed ut perspiciatis</p>", "<p>unde omnis iste natus</p>"]
```

## position
Return position of the selected node in relation to its parent.
Can be used with `slice()`.

```elixir
iex> ModestEx.position("<p>Hello</p><div></div><p>World</p>", "p")
[1, 3]
```

## wrap
Wrap an HTML structure around each element in the set of matched elements.

```elixir
iex> ModestEx.wrap("<p>Hello</p><p>World</p>", "p", "<div class=\"wrapper\">")
"<div class=\"wrapper\"><p>Hello</p></div><div class=\"wrapper\"><p>World</p></div>"
```

## pretty_print
Use `IO.puts` to pretty print html tree to `stdout`.

```elixir
iex> ModestEx.pretty_print("<p>Hello World</p>")
"\e[31m<\e[0m\e[31mp\e[0m\e[31m>\e[0m\e[0mHello World\e[0m\e[31m</\e[0m\e[31mp\e[0m\e[31m>\e[0m\n"
```

## transform
Transform a html string by a list of transformation instructions. See `compare`. 

```elixir
iex> ModestEx.transform("<div>Hello</div>", [{:set_attribute, "div", "class", "greeting"}, {:append, "div", "<span>World</span>"}])
"<div class=\"greeting\">Hello<span>World</span></div>"
```