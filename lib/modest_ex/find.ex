defmodule ModestEx.Find do
  @moduledoc false

  def find([bin | rest], selector) when is_bitstring(selector) do
    find(bin, selector) ++ find(rest, selector)
  end

  def find([], _), do: []

  def find(bin, selector) when is_bitstring(bin) when is_bitstring(selector) do
    ModestEx.LexborHelper.ensure_started()

    with {:ok, doc} <- :lexbor_erl.parse(bin),
         {:ok, nodes} <- :lexbor_erl.select(doc, selector),
         html_list <- get_outer_html_for_nodes(doc, nodes),
         :ok <- :lexbor_erl.release(doc) do
      ModestEx.resolve(html_list)
    else
      {:error, _reason} = error ->
        error

      error ->
        {:error, error}
    end
  end

  defp get_outer_html_for_nodes(doc, nodes) do
    nodes
    |> Enum.map(fn node ->
      case :lexbor_erl.outer_html(doc, node) do
        {:ok, html} -> html
        _ -> nil
      end
    end)
    |> Enum.reject(&is_nil/1)
    |> Enum.reject(&is_document_structure?/1)
  end

  # Filter out document structure elements that lexbor_erl adds during parsing
  defp is_document_structure?(html) when is_binary(html) do
    # Filter out empty head tags
    # Filter out body tags (body element with or without content)
    html == "<head></head>" or
      Regex.match?(~r/^<body[^>]*>.*<\/body>$/s, html)
  end
end
