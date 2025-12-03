defmodule ModestEx.GetAttribute do
  @moduledoc false

  def get_attribute([bin | bins], key) when is_bitstring(key) do
    get_attribute(bin, key) ++ get_attribute(bins, key)
  end

  def get_attribute([], _), do: []

  def get_attribute(bin, key) when is_bitstring(bin) when is_bitstring(key) do
    # Select all elements with that attribute
    get_attribute(bin, "[#{key}]", key)
  end

  def get_attribute([bin | bins], selector, key)
      when is_bitstring(selector)
      when is_bitstring(key) do
    get_attribute(bin, selector, key) ++ get_attribute(bins, selector, key)
  end

  def get_attribute([], _, _), do: []

  def get_attribute(bin, selector, key)
      when is_bitstring(bin)
      when is_bitstring(selector)
      when is_bitstring(key) do
    ModestEx.LexborHelper.ensure_started()

    with {:ok, doc} <- :lexbor_erl.parse(bin),
         {:ok, nodes} <- :lexbor_erl.select(doc, selector),
         values <- get_attribute_values(doc, nodes, key),
         :ok <- :lexbor_erl.release(doc) do
      ModestEx.resolve(values)
    else
      {:error, _reason} = error ->
        error

      error ->
        {:error, error}
    end
  end

  defp get_attribute_values(doc, nodes, key) do
    Enum.map(nodes, fn node ->
      case :lexbor_erl.get_attribute(doc, node, key) do
        {:ok, value} when is_binary(value) -> value
        {:ok, :undefined} -> nil
        _ -> nil
      end
    end)
    |> Enum.reject(&is_nil/1)
  end
end
