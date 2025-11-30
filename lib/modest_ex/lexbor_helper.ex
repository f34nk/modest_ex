defmodule ModestEx.LexborHelper do
  @moduledoc false

  @doc """
  Ensure lexbor_erl application is started.
  Returns :ok if already started or successfully started.
  """
  def ensure_started do
    case :lexbor_erl.alive() do
      true -> :ok
      false -> :lexbor_erl.start()
    end
  end

  @doc """
  Parse HTML, execute function with document, then ensure release.

  This helper ensures proper document lifecycle management by automatically
  releasing the document after the function executes, even if an error occurs.

  ## Examples

      with_doc("<div>Hello</div>", fn doc ->
        :lexbor_erl.select(doc, "div")
      end)
  """
  def with_doc(html, fun) when is_binary(html) and is_function(fun, 1) do
    ensure_started()

    case :lexbor_erl.parse(html) do
      {:ok, doc} ->
        try do
          fun.(doc)
        after
          :lexbor_erl.release(doc)
        end

      error ->
        error
    end
  end

  @doc """
  Extract body children from full HTML document.

  Extracts only the children of the <body> element, excluding the body tag itself.
  This maintains compatibility with ModestEx's :body_children scope.

  ## Examples

      extract_body_children("<html><head></head><body><div>Hello</div></body></html>")
      # => "<div>Hello</div>"
  """
  def extract_body_children(html) when is_binary(html) do
    # Use regex to extract content between <body> and </body>
    case Regex.run(~r/<body[^>]*>(.*?)<\/body>/s, html) do
      [_, body_content] -> body_content
      nil -> html
    end
  end

  @doc """
  Extract body element from full HTML document.

  Extracts the <body> element including the body tag itself.
  This maintains compatibility with ModestEx's :body scope.

  ## Examples

      extract_body("<html><head></head><body><div>Hello</div></body></html>")
      # => "<body><div>Hello</div></body>"
  """
  def extract_body(html) when is_binary(html) do
    case Regex.run(~r/(<body[^>]*>.*?<\/body>)/s, html) do
      [_, body_element] -> body_element
      nil -> html
    end
  end

  @doc """
  Extract head element from full HTML document.

  Extracts the <head> element including the head tag itself.
  This maintains compatibility with ModestEx's :head scope.

  ## Examples

      extract_head("<html><head><title>Test</title></head><body></body></html>")
      # => "<head><title>Test</title></head>"
  """
  def extract_head(html) when is_binary(html) do
    case Regex.run(~r/(<head[^>]*>.*?<\/head>)/s, html) do
      [_, head_element] -> head_element
      nil -> html
    end
  end

  @doc """
  Apply ModestEx scope to serialized HTML output.

  Transforms full HTML documents to the specified scope format to maintain
  compatibility with ModestEx's scope configuration.

  ## Scope Options

  - `:html` - Return full HTML document (no transformation)
  - `:body_children` - Return only children of body element
  - `:body` - Return body element with tag
  - `:head` - Return head element with tag

  ## Examples

      apply_scope(html, :html)
      # => "<html><head></head><body><div>Hello</div></body></html>"

      apply_scope(html, :body_children)
      # => "<div>Hello</div>"
  """
  def apply_scope(html, :html), do: html
  def apply_scope(html, :body_children), do: extract_body_children(html)
  def apply_scope(html, :body), do: extract_body(html)
  def apply_scope(html, :head), do: extract_head(html)
  def apply_scope(html, _unknown), do: html

  @doc """
  Raise an error indicating a feature is not yet implemented.

  Provides a helpful error message with suggestions for users who attempt
  to use features that are not yet supported with the lexbor_erl backend.

  ## Examples

      not_implemented("position/2")
  """
  def not_implemented(feature_name) do
    raise RuntimeError, """
    ModestEx.#{feature_name} is not yet implemented with lexbor_erl backend.

    This feature is not currently supported because lexbor_erl does not provide
    the necessary functionality. If you need this feature, please consider:

    1. Using ModestEx 1.x (the previous version with Modest backend)
    2. Contributing to lexbor_erl to add the missing functionality
    3. Opening an issue at https://github.com/f34nk/modest_ex/issues
    """
  end
end
