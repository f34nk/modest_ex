defmodule ModestEx.Remove do
  @moduledoc false

  def remove([bin | rest], selector) when is_bitstring(selector) do
    [remove(bin, selector)] ++ remove(rest, selector)
  end

  def remove([], _), do: []

  def remove(bin, selector) when is_bitstring(bin) when is_bitstring(selector) do
    ModestEx.LexborHelper.ensure_started()

    with {:ok, doc} <- :lexbor_erl.parse(bin),
         {:ok, nodes} <- :lexbor_erl.select(doc, selector),
         :ok <- remove_nodes(doc, nodes),
         {:ok, result} <- :lexbor_erl.serialize(doc),
         :ok <- :lexbor_erl.release(doc) do
      ModestEx.LexborHelper.apply_scope(result, Application.get_env(:modest_ex, :scope))
    else
      {:error, reason} ->
        {:error, to_string(reason)}

      error ->
        {:error, "Failed to remove nodes: #{inspect(error)}"}
    end
  end

  defp remove_nodes(doc, nodes) do
    results =
      Enum.map(nodes, fn node ->
        :lexbor_erl.remove_node(doc, node)
      end)

    if Enum.all?(results, &(&1 == :ok)) do
      :ok
    else
      {:error, "Failed to remove some nodes"}
    end
  end
end
