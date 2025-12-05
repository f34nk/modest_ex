defmodule ModestEx.Serialize do
  @moduledoc false

  def serialize([bin | rest], scope) do
    serialize(bin, scope) ++ serialize(rest, scope)
  end

  def serialize([], _), do: []

  def serialize(bin, scope) when is_bitstring(bin) and is_atom(scope) do
    ModestEx.LexborHelper.ensure_started()

    case :lexbor_erl.parse_serialize(bin) do
      {:ok, full_html} ->
        ModestEx.LexborHelper.apply_scope(full_html, scope)

      {:error, _reason} = error ->
        error
    end
  end
end
