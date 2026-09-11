import os
import glob
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter

try:
    from scipy.interpolate import PchipInterpolator
    SCIPY_DISPONIBLE = True
except ImportError:
    SCIPY_DISPONIBLE = False

# Dimensiones válidas según el enunciado (Anexo A.2): 2^4, 2^6, 2^8, 2^10
DIMENSIONES_VALIDAS = [16, 64, 256, 1024]


def leer_mediciones(ruta_mediciones):
    """Lee los archivos de mediciones de matrices y los convierte en un DataFrame."""
    archivos = glob.glob(os.path.join(ruta_mediciones, "*_measurements.txt"))
    datos = []

    for archivo in archivos:
        partes = os.path.basename(archivo).split('_')
        if len(partes) < 6:
            continue
        try:
            n = int(partes[0])
            if n not in DIMENSIONES_VALIDAS:
                continue

            tipo, dominio = partes[1], partes[2]   # ej: densa, D0
            algoritmo = partes[4].capitalize()     # Naive, Strassen

            tiempo, memoria = 0.0, 0
            with open(archivo, 'r') as f:
                for linea in f:
                    if linea.startswith("Tiempo_ms:"):
                        tiempo = float(linea.split(":")[1].strip())
                    elif linea.startswith("Memoria_KB:"):
                        memoria = int(linea.split(":")[1].strip())

            datos.append({
                'N': n,
                'Configuración': f"{tipo}_{dominio}",
                'Algoritmo': algoritmo,
                'Tiempo (ms)': tiempo,
                'Memoria (KB)': memoria
            })
        except Exception as e:
            print(f"⚠️  No se pudo procesar {archivo}: {e}")

    return pd.DataFrame(datos)


def curva_suave(x, y, num=200):
    x = np.asarray(x, dtype=float)
    y = np.asarray(y, dtype=float)
    if len(x) < 3 or not SCIPY_DISPONIBLE:
        return x, y  
    y = np.clip(y, 1e-9, None) 
    lx, ly = np.log10(x), np.log10(y)
    orden = np.argsort(lx)
    lx, ly = lx[orden], ly[orden]
    if len(np.unique(lx)) < 3:
        return x, y
    pchip = PchipInterpolator(lx, ly)
    lx_denso = np.linspace(lx.min(), lx.max(), num)
    return 10 ** lx_denso, 10 ** pchip(lx_denso)

def generar_graficos(df, ruta_plots):
    os.makedirs(ruta_plots, exist_ok=True)
    sns.set_theme(style="whitegrid", font="sans-serif", font_scale=1.1)
    plt.rcParams.update({
        'figure.facecolor': 'white',
        'axes.facecolor': 'white',
        'axes.edgecolor': '#333333',
        'grid.color': '#e0e0e0',
        'grid.linestyle': '--',
        'grid.alpha': 0.6,
        'axes.axisbelow': True,
    })
    metricas = {
        'Tiempo (ms)': {
            'ylabel': 'Tiempo de Ejecución (ms)',
            'filename': 'tiempo',
            'palette': 'colorblind'
        },
        'Memoria (KB)': {
            'ylabel': 'Consumo de Memoria (KB)',
            'filename': 'memoria',
            'palette': 'muted'
        }
    }
    for config in sorted(df['Configuración'].unique()):
        df_config = df[df['Configuración'] == config]
        config_display = config.replace('_', ' ').title()
        ticks_x = sorted(df_config['N'].unique())

        for metrica, info in metricas.items():
            fig, ax = plt.subplots(figsize=(10, 6.5))

            df_prom = df_config.groupby(['Algoritmo', 'N'], as_index=False)[metrica].mean()
            algoritmos = sorted(df_prom['Algoritmo'].unique())
            colores = sns.color_palette(info['palette'], n_colors=len(algoritmos))
            for i, alg in enumerate(algoritmos):
                df_alg = df_prom[df_prom['Algoritmo'] == alg].sort_values('N')
                color = colores[i]
                xs, ys = curva_suave(df_alg['N'].values, df_alg[metrica].values)
                ax.plot(xs, ys, color=color, linewidth=2.2, alpha=0.9, label=alg)
                ax.scatter(df_alg['N'], df_alg[metrica], color=color, s=45,
                           edgecolors='white', linewidth=1.2, zorder=3)
            ax.set_xscale('linear')
            ax.set_yscale('linear')
            ax.set_xticks(ticks_x)
            ax.xaxis.set_major_formatter(FuncFormatter(lambda x, _: f'{int(x)}'))
            ax.yaxis.set_major_formatter(FuncFormatter(lambda y, _: f'{y:g}'))
            ax.set_xlim(0, ticks_x[-1] * 1.05)
            ax.set_ylim(0, df_prom[metrica].max() * 1.10)
            ax.minorticks_off()
            ax.set_title(
                f"Multiplicación de Matrices: {metrica.split(' ')[0]}\n"
                f"{config_display}",
                fontsize=15, fontweight='bold', pad=15
            )
            ax.set_xlabel('Dimensión de la Matriz (N × N)', fontsize=12, fontweight='semibold')
            ax.set_ylabel(info['ylabel'], fontsize=12, fontweight='semibold')

            ax.legend(
                title='Algoritmo',
                loc='upper left',
                frameon=True, fancybox=True, shadow=True,
                framealpha=0.95, fontsize=10
            )
            ax.get_legend().get_title().set_fontweight('bold')

            ax.grid(True, which='major', alpha=0.35, linestyle='--')
            ax.grid(False, which='minor')

            plt.tight_layout()

            filename = f"{info['filename']}_{config}.png"
            plt.savefig(
                os.path.join(ruta_plots, filename),
                dpi=300, bbox_inches='tight', facecolor='white'
            )
            plt.close()


if __name__ == "__main__":
    RUTA_MEDICIONES = "../data/measurements"
    RUTA_PLOTS = "../data/plots"
    if not SCIPY_DISPONIBLE:
        print(" falta pip install scipy")
    df = leer_mediciones(RUTA_MEDICIONES)
    if not df.empty:
        generar_graficos(df, RUTA_PLOTS)
        print(f"\nSe guardaron en la ruta: {os.path.abspath(RUTA_PLOTS)}")
    else:
        print(f"\nError, no hay mediciones en:  {os.path.abspath(RUTA_MEDICIONES)}")