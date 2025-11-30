defmodule ModestEx.GetText do
  @moduledoc false

  def get_text([bin | bins]) do
    get_text(bin) ++ get_text(bins)
  end

  def get_text([]), do: []

  def get_text(bin) when is_bitstring(bin) do
    ModestEx.LexborHelper.ensure_started()

    with {:ok, doc} <- :lexbor_erl.parse(bin),
         {:ok, nodes} <- :lexbor_erl.select(doc, "body"),
         [body_node] <- nodes,
         {:ok, text} <- :lexbor_erl.get_text(doc, body_node),
         :ok <- :lexbor_erl.release(doc) do
      text
    else
      {:error, reason} ->
        {:error, to_string(reason)}

      [] ->
        ""

      error ->
        {:error, "Failed to get text: #{inspect(error)}"}
    end
  end

  def get_text([bin | bins], selector) when is_bitstring(selector) do
    get_text(bin, selector) ++ get_text(bins, selector)
  end

  def get_text([], _), do: []

  def get_text(bin, selector) when is_bitstring(bin) when is_bitstring(selector) do
    ModestEx.LexborHelper.ensure_started()

    with {:ok, doc} <- :lexbor_erl.parse(bin),
         {:ok, nodes} <- :lexbor_erl.select(doc, selector),
         texts <-
           Enum.map(nodes, fn node ->
             case :lexbor_erl.get_text(doc, node) do
               {:ok, text} -> text
               _ -> ""
             end
           end),
         :ok <- :lexbor_erl.release(doc) do
      ModestEx.resolve(texts)
    else
      {:error, reason} ->
        {:error, to_string(reason)}

      error ->
        {:error, "Failed to get text: #{inspect(error)}"}
    end
  end
end
