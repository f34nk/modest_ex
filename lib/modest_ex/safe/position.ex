defmodule ModestEx.Safe.Position do
  @moduledoc false

  defp to_integer([bin | rest]) when is_binary(bin) do
    [to_integer(bin)] ++ to_integer(rest)
  end

  defp to_integer([]), do: []

  defp to_integer(""), do: nil

  defp to_integer(bin) when is_binary(bin) do
    String.to_integer(bin)
  end

  def position(bin, selector) do
    case Nodex.Cnode.call(
           ModestEx.Safe.Cnode,
           {:position, bin <> "\0", selector <> "\0", ModestEx.delimiter() <> "\0"}
         ) do
      {:ok, {:position, result}} -> to_integer(result)
      _ -> {:error, bin}
    end
  end
end
