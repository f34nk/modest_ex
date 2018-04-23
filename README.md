### *First major release coming soon!!!*

[![Build status](https://travis-ci.org/f34nk/modest_ex.svg?branch=master)](https://travis-ci.org/f34nk/modest_ex)
[![ModestEx version](https://img.shields.io/hexpm/v/modest_ex.svg)](https://hex.pm/packages/modest_ex)
[![Hex.pm](https://img.shields.io/hexpm/dt/modest_ex.svg)](https://hex.pm/packages/modest_ex)

![humble by Eliricon from the Noun Project](https://github.com/f34nk/modest_ex/blob/master/modest_ex_icon.png)

# ModestEx

A library to do pipeable transformations on html strings with CSS selectors, e.g. find(), prepend(), append(), replace() etc.

Elixir/Erlang bindings for lexborisov's **Modest**

>Modest is a fast HTML renderer implemented as a pure C99 library with no outside dependencies.

- [Modest](https://github.com/lexborisov/Modest)
  - HTML5 parsing library in pure C99
  - fully conformant with the HTML5 spec
  - [modest_html](https://github.com/f34nk/modest_html) (Wrapper library)

The binding is implemented as a **C-Node** following the excellent example in Overbryd's package **nodex**. If you want to learn how to set up bindings to C/C++, you should definitely check it out.

- [nodex](https://github.com/Overbryd/nodex)
  - distributed Elixir
  - save binding with C-Nodes

>C-Nodes are external os-processes that communicate with the Erlang VM through erlang messaging. That way you can implement native code and call into it from Elixir in a safe predictable way. The Erlang VM stays unaffected by crashes of the external process.

## Example

Total **16** features implemented. See [**complete feature list**](https://github.com/f34nk/modest_ex/blob/master/FEATURES.md).

Build transformation pipelines...

```elixir
test "build up a complete DOM" do
  result = ""
  |> ModestEx.serialize()
  |> ModestEx.append("body", "<div>")
  |> ModestEx.set_attribute("div", "class", "col-md-12")
  |> ModestEx.append("div", "<div>")
  |> ModestEx.set_attribute("div.col-md-12 div", "class", "col-md-6")
  |> ModestEx.append("div.col-md-12 div", "<a></a>")
  |> ModestEx.set_text("a", "Hello")

  copy = ModestEx.find(result, "div.col-md-12 div")
  |> ModestEx.set_text("a", "World")
  
  result = ModestEx.insert_after(result, "div.col-md-12 div", copy)
  |> ModestEx.set_attribute("div.col-md-6:first-of-type a", "href", "https://elixir-lang.org")
  |> ModestEx.set_attribute("div.col-md-6:last-of-type a", "href", "https://google.de")
  
  assert result == "<div class=\"col-md-12\"><div class=\"col-md-6\"><a href=\"https://elixir-lang.org\">Hello</a></div><div class=\"col-md-6\"><a href=\"https://google.de\">World</a></div></div>"
end
```

## Supported CSS Selectors

All common CSS Selectors are supported. Total **38** selector patterns implemented.
See [**complete list of supported CSS selectors**](https://github.com/f34nk/modest_ex/blob/master/SELECTORS.md).

## Installation

Available on [hex](https://hex.pm/packages/modest_ex).

```elixir
def deps do
  [
    {:modest_ex, "~> 1.0.0"}
  ]
end
```

## Target dependencies
```
cmake 3.x
erlang-dev
erlang-xmerl
erlang-parsetools
```
## Compile and test
```
mix deps.get
mix compile
mix test
```
## Cloning
```
git clone git@github.com:f34nk/modest_ex.git
cd modest_ex
```
All binding targets are added as submodules in the `target/` folder.
```
git submodule update --init --recursive --remote
mix deps.get
mix compile
mix test
mix test.target
```
Cleanup
```
mix clean
```
Benchmark
```
mix bench
```
## Roadmap

See [CHANGELOG](https://github.com/f34nk/modest_ex/blob/master/CHANGELOG.md).

- [ ] Bindings
  - [x] Call as C-Node
  - [ ] Call as dirty-nif
- [ ] Tests
  - [x] Call as C-Node
  - [ ] Call as dirty-nif
  - [x] Target tests
  - [x] Feature tests
  - [x] Package test
- [ ] Features
  - [x] Find nodes using a CSS selector
  - [x] Serialize any string with valid or broken html
  - [x] Get attribute with optional CSS selector
  - [x] Set attribute with optional CSS selector
  - [x] Get text with optional CSS selector
  - [x] Set text with optional CSS selector
  - [x] Remove a node from html
  - [x] Append node to another node
  - [x] Prepend node to another node
  - [x] Insert node before another node
  - [x] Insert node after another node
  - [x] Replace node with another node
  - [x] Slice html to a subset of nodes
  - [x] Get position of node in relation to its parent
  - [x] Wrap node with another node
  - [x] Pretty print html
  - [ ] Compare two html strings (see [here](https://github.com/f34nk/modest_html/blob/master/CHANGELOG.md#200))
  - [ ] Transform html string by list of actions
- [x] Custom CSS selector for pseudo class ":contains(text)" implemented in [Modest](https://github.com/lexborisov/Modest/pull/42)
- [x] Scope flag to control serialization
- [x] List of supported CSS Selectors
- [ ] Documentation
- [x] Publish as hex package

## License

ModestEx is under LGPL license. Check the [LICENSE](https://github.com/f34nk/modest_ex/blob/master/LICENSE) file for more details.


## Icon Credit

humble by Eliricon from the Noun Project