defmodule ModestEx.Replace do
  @moduledoc false

  def replace([bin | rest], selector, new_bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    [replace(bin, selector, new_bin)] ++ replace(rest, selector, new_bin)
  end

  def replace([], _, _), do: []

  def replace(bin, selector, new_bin)
      when is_bitstring(bin)
      when is_bitstring(selector)
      when is_bitstring(new_bin) do
    ModestEx.LexborHelper.ensure_started()

    scope = Application.get_env(:modest_ex, :scope, :body_children)

    with {:ok, doc} <- :lexbor_erl.parse(bin),
         {:ok, _num_matches} <- :lexbor_erl.replace_content(doc, selector, new_bin),
         {:ok, result} <- :lexbor_erl.serialize(doc),
         :ok <- :lexbor_erl.release(doc) do
      ModestEx.LexborHelper.apply_scope(result, scope)
    else
      {:error, _reason} = error ->
        error

      error ->
        {:error, error}
    end
  end
end
