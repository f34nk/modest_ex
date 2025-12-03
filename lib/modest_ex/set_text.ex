defmodule ModestEx.SetText do
  @moduledoc false

  def set_text([bin | bins], selector, [text | texts]) when is_bitstring(selector) do
    [set_text(bin, selector, text)] ++ set_text(bins, selector, texts)
  end

  def set_text([bin | bins], selector, text)
      when is_bitstring(selector)
      when is_bitstring(text) do
    [set_text(bin, selector, text)] ++ set_text(bins, selector, text)
  end

  def set_text([], _, _), do: []

  def set_text(bin, selector, text)
      when is_bitstring(bin)
      when is_bitstring(selector)
      when is_bitstring(text) do
    ModestEx.LexborHelper.ensure_started()

    with {:ok, doc} <- :lexbor_erl.parse(bin),
         {:ok, nodes} <- :lexbor_erl.select(doc, selector),
         :ok <- set_text_on_nodes(doc, nodes, text),
         {:ok, result} <- :lexbor_erl.serialize(doc),
         :ok <- :lexbor_erl.release(doc) do
      ModestEx.LexborHelper.apply_scope(result, Application.get_env(:modest_ex, :scope))
    else
      {:error, reason} ->
        {:error, to_string(reason)}

      error ->
        {:error, "Failed to set text: #{inspect(error)}"}
    end
  end

  defp set_text_on_nodes(doc, nodes, text) do
    results =
      Enum.map(nodes, fn node ->
        :lexbor_erl.set_text(doc, node, text)
      end)

    if Enum.all?(results, &(&1 == :ok)) do
      :ok
    else
      {:error, "Failed to set text on some nodes"}
    end
  end
end
