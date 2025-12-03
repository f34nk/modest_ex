defmodule ModestEx.SetAttribute do
  @moduledoc false

  def set_attribute([bin | bins], selector, key, [value | values])
      when is_bitstring(selector)
      when is_bitstring(key) do
    [set_attribute(bin, selector, key, value)] ++ set_attribute(bins, selector, key, values)
  end

  def set_attribute([bin | bins], selector, key, value)
      when is_bitstring(selector)
      when is_bitstring(key)
      when is_bitstring(value) do
    [set_attribute(bin, selector, key, value)] ++ set_attribute(bins, selector, key, value)
  end

  def set_attribute([], _, _, _), do: []

  def set_attribute(bin, selector, key, value)
      when is_bitstring(bin)
      when is_bitstring(selector)
      when is_bitstring(key)
      when is_bitstring(value) do
    ModestEx.LexborHelper.ensure_started()

    with {:ok, doc} <- :lexbor_erl.parse(bin),
         {:ok, nodes} <- :lexbor_erl.select(doc, selector),
         :ok <- set_attributes_on_nodes(doc, nodes, key, value),
         {:ok, result} <- :lexbor_erl.serialize(doc),
         :ok <- :lexbor_erl.release(doc) do
      ModestEx.LexborHelper.apply_scope(result, Application.get_env(:modest_ex, :scope))
    else
      {:error, reason} ->
        {:error, to_string(reason)}

      error ->
        {:error, "Failed to set attribute: #{inspect(error)}"}
    end
  end

  defp set_attributes_on_nodes(doc, nodes, key, value) do
    results =
      Enum.map(nodes, fn node ->
        :lexbor_erl.set_attribute(doc, node, key, value)
      end)

    if Enum.all?(results, &(&1 == :ok)) do
      :ok
    else
      {:error, "Failed to set attribute on some nodes"}
    end
  end
end
