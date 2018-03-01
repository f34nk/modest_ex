defmodule ModestEx do
  @moduledoc """
  This module exposes features to find html nodes with CSS selectors and common methods to manipulate the DOM tree.

  ## Credits:

  The package implements bindings to [Alexander Borisov's Modest](https://github.com/lexborisov/Modest). 
  The binding is implemented as a C-Node based on the excellent example of [Lukas Rieder's cnodex](https://github.com/Overbryd/nodex) and [myhtmlex](https://github.com/Overbryd/myhtmlex).

  ## Example

    iex> ModestEx.find("<p><a>Hello</a> World</p>", "p a")
    ["<a>Hello</a>"]

  """

  @type success() :: String.t | [String.t]
  @type error() :: {:error, String.t}

  @doc """
  Parse html string and find nodes with a CSS selector.
  Returns nodes as list of html strings delimited by delimiter

  ## Examples

    iex> ModestEx.find("<p><a>Hello</a> World</p>", "p a", "|")
    "<a>Hello</a>"

    iex> ModestEx.find("<p><span>Hello</span> <span>World</span></p>", "span", "|")
    "<span>Hello</span>|<span>World</span>"

  """
  @spec find(String.t, String.t, String.t) :: success() | error()
  def find(bin, selector, delimiter) when is_binary(bin) do
    ModestEx.Safe.find(bin, selector, delimiter)
  end

  @doc """
  Parse html string and find nodes with a CSS selector.
  Returns nodes as list of html strings.

  ## Examples

    iex> ModestEx.find("<p><a>Hello</a> World</p>", "p a")
    ["<a>Hello</a>"]

    iex> ModestEx.find("<p><span>Hello</span> <span>World</span></p>", "span")
    ["<span>Hello</span>", "<span>World</span>"]

  """
  @spec find(String.t, String.t) :: success() | error()
  def find(bin, selector) when is_binary(bin) do
    ModestEx.Safe.find(bin, selector)
  end

  @doc """
  Serialize any string with valid or broken html.
  Returns valid html string.

  ## Examples

    iex> ModestEx.serialize("<div>Hello<span>World")
    "<html><head></head><body><div>Hello<span>World</span></div></body></html>"

  """
  @spec serialize(String.t) :: success() | error()
  def serialize(bin) when is_binary(bin) do
    ModestEx.Safe.serialize(bin)
  end

end
