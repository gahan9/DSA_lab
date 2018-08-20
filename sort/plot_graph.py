import os
import plotly
import plotly.graph_objs as go

import pandas as pd
from faker import Faker

faker = Faker()

STORAGE_DIR = os.path.join(".", "analysis")
os.makedirs(STORAGE_DIR, exist_ok=True)

df_sample = pd.read_csv('https://raw.githubusercontent.com/gahan9/DSA_lab/master/sort/analysis_test.csv')

color = ["#ff7c00", "#a91f78", "#0432ff", "#00a643", "#a6f900", "#fffb00", "#ffd300", "#c8e000"]
# df_sample = df_sample.loc[df_sample['log10(DATA_SET)'] != 4.69]
ALGORITHMS = [
    'Bubble_sort_(Iterative)',
    'Heap_sort_(Recursive)',
    'Insertion_sort_(Iterative)',
    'Merge_sort_(Recursive)',
    'Quick_sort_(Recursive)',
    'Selection_sort_(Iterative)'
]
def plot_graph(algo_name):
    data = []
    df_filtered = df_sample.loc[df_sample['ALGORITHM'] == algo_name]
    data_set_type = ['ascending', 'descending', 'random', 'same']
    # data_set_type = ['ascending', 'descending', 'random']
    # fig = plotly.tools.make_subplots(rows=6, cols=2,
    #                                  specs=[[{}, {'rowspan': 2}],
    #                                         [{}, None],
    #                                         [{'rowspan': 2}, None],
    #                                         [None, None],
    #                                         [None, None],
    #                                         [{}, {}]],
    #                                  print_grid=False)
    # trace_cnt = 1
    # for algo in ALGORITHMS:
    cnt = 0
    for i in data_set_type:
        data_algo_type = df_filtered.loc[df_filtered['DATA_SET_TYPE'] == i]
        y = data_algo_type['TIME'].mul(1000).tolist()  # convert time in milliseconds
        x = data_algo_type['DATA_SET'].tolist()  # data set
        x = data_algo_type['log10(DATA_SET)'].tolist()  # log10 to data set
        trace = go.Scatter(x=x, y=y, text=[], hovertext=[], name=i, marker=dict(color=color[cnt]))
        data += [trace]
        cnt += 1
        #     fig.append_trace(trace, trace_cnt, 1)
        #     fig.append_trace(trace, trace_cnt, 2)
        # trace_cnt += 1
    layout = go.Layout(title=algo_name, barmode='group',
                       xaxis={'title': 'data set (considering log base 10)', 'tickformat': ',d'},
                       yaxis={'title': 'time (ms)', 'tickformat': ',d'})
    # fig['layout'].update(height=600, width=600, title='specs examples')

    html_path = os.path.join(STORAGE_DIR, '{}.{}'.format(algo_name, 'html'))
    img_path = os.path.join(STORAGE_DIR, '{}.{}'.format(algo_name, 'png'))
    fig = go.Figure(data=data, layout=layout)
    plotly.offline.plot(fig, validate=False, auto_open=False, filename=html_path)
    plotly.plotly.image.save_as(fig, filename=img_path)


if __name__ == "__main__":
    list(map(plot_graph, ALGORITHMS))