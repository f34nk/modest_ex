defmodule ModestEx.MixProject do
  use Mix.Project

  def project do
    [
      app: :modest_ex,
      version: "1.0.3",
      elixir: "~> 1.5",
      compilers: [:modest_ex_compile] ++ Mix.compilers(),
      build_embedded: Mix.env() == :prod,
      start_permanent: Mix.env() == :prod,
      name: "ModestEx",
      description: """
        ModestEx - A library to do pipeable transformations on html strings with CSS selectors, e.g. find(), prepend(), append(), replace() etc.
        Erlang/Elixir binding to Alexander Borisov's Modest.
        Implemented as a C-Node based on the excellent example of Lukas Rieder's cnodex.
      """,
      docs: docs(),
      deps: deps(),
      package: package()
    ]
  end

  defp docs do
    [
      main: "ModestEx"
    ]
  end

  def package do
    [
      maintainers: ["Frank Eickhoff"],
      licenses: ["GNU LGPL"],
      links: %{
        "Github" => "https://github.com/f34nk/modest_ex",
        "Issues" => "https://github.com/f34nk/modest_ex/issues",
        "cnodex" => "https://github.com/Overbryd/nodex",
        "modest_html" => "https://github.com/f34nk/modest_html",
        "Modest" => "https://github.com/lexborisov/Modest"
      },
      files: [
        "lib",
        "target",
        "test",
        "priv/compile.sh",
        "priv/clean.sh",
        "priv/test.sh",
        "mix.exs",
        "README.md",
        "LICENSE"
      ]
    ]
  end

  def application do
    [
      extra_applications: [:logger],
      mod: {ModestEx.Safe, []},
      # used to detect conflicts with other applications named processes
      registered: [ModestEx.Safe.Cnode, ModestEx.Safe.Supervisor],
      env: [
        mode: ModestEx.Safe
      ]
    ]
  end

  defp deps do
    [
      # documentation helpers
      {:ex_doc, ">= 0.0.0", only: :dev},
      # benchmarking helpers
      {:benchfella, "~> 0.3.0", only: :dev},
      # cnode helpers
      {:nodex, "~> 0.1.1"}
    ]
  end
end

defmodule Shell do
  def exec(exe, args, opts \\ [:stream]) when is_list(args) do
    port =
      Port.open(
        {:spawn_executable, exe},
        opts ++ [{:args, args}, :binary, :exit_status, :hide, :use_stdio, :stderr_to_stdout]
      )

    handle_output(port)
  end

  def handle_output(port) do
    receive do
      {^port, {:data, data}} ->
        # Replace this with the appropriate broadcast
        IO.binwrite(data)
        handle_output(port)

      {^port, {:exit_status, status}} ->
        status
    end
  end
end

defmodule Mix.Tasks.Compile.ModestExCompile do
  def run(_) do
    if match?({:win32, _}, :os.type()) do
      IO.warn("Windows is not supported yet.")
      exit(1)
    else
      Shell.exec("priv/compile.sh", [])
    end

    :ok
  end

  def clean() do
    Shell.exec("priv/clean.sh", [])
    :ok
  end
end

defmodule Mix.Tasks.Test.Target do
  def run(_) do
    if match?({:win32, _}, :os.type()) do
      IO.warn("Windows is not supported yet.")
      exit(1)
    else
      Shell.exec("priv/test.sh", [])
    end

    :ok
  end
end
