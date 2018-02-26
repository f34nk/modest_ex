defmodule ModestEx.MixProject do
  use Mix.Project

  def project do
    [
      app: :modest_ex,
      version: "0.1.0",
      elixir: "~> 1.5",
      compilers: [:modest_ex_compile] ++ Mix.compilers,
      build_embedded: Mix.env == :prod,
      start_permanent: Mix.env() == :prod,
      name: "ModestEx",
      description: """
        Modest is a fast HTML renderer implemented as a pure C99 library with no outside dependencies.
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
        "gumbo-query" => "https://github.com/lazytiger/gumbo-query",
        "gumbo-parser" => "https://github.com/google/gumbo-parser"
      },
      files: [
        "lib",
        "target",
        "test",
        "compile.sh",
        "clean.sh",
        "test.sh",
        "mix.exs",
        "README.md",
        "LICENSE"
      ]
    ]
  end

  # Run "mix help compile.app" to learn about applications.
  def application do
    [
      extra_applications: [:logger]
    ]
  end

  # Run "mix help deps" to learn about dependencies.
  defp deps do
    [
      # documentation helpers
      {:ex_doc, ">= 0.0.0", only: :docs},
      # benchmarking helpers
      {:benchfella, "~> 0.3.0", only: :dev},
      # cnode helpers
      {:nodex, "~> 0.1.1"},
      {:mix_test_watch, "~> 0.5", only: :dev, runtime: false}
    ]
  end
end

defmodule Shell do
  def exec(exe, args, opts \\ [:stream]) when is_list(args) do
    port = Port.open({:spawn_executable, exe}, opts ++ [{:args, args}, :binary, :exit_status, :hide, :use_stdio, :stderr_to_stdout])
    handle_output(port)
  end

  def handle_output(port) do
    receive do
      {^port, {:data, data}} ->
        IO.binwrite(data) # Replace this with the appropriate broadcast
        handle_output(port)
      {^port, {:exit_status, status}} ->
        status
    end
  end
end

defmodule Mix.Tasks.Compile.ModestExCompile do
  def run(_) do
    if match? {:win32, _}, :os.type do
      IO.warn "Windows is not supported yet."
      exit(1)
    else
      Shell.exec(System.cwd() <> "/compile.sh", [to_string(Mix.env)])
    end
    :ok
  end

  def clean() do
    Shell.exec(System.cwd() <> "/clean.sh", [])
    :ok
  end
end

defmodule Mix.Tasks.Test.Target do
  def run(_) do
    if match? {:win32, _}, :os.type do
      IO.warn "Windows is not supported yet."
      exit(1)
    else
      Shell.exec(System.cwd() <> "/test.sh", [])
    end
    :ok
  end
end